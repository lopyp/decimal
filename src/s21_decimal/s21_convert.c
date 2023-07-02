#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_decimal value = {.bits = {0U, 0U, 0U, 0U}};
  const int INT_MIN = -0x7FFFFFFF - 1;
  if (src == INT_MIN) {
    set_sgn(&value, INT_MIN < 0);
    value.bits[0] = INT_MIN;
  } else {
    if (src < 0) {
      set_sgn(&value, 1);
      src = -src;
    }
    value.bits[0] = (unsigned int)src;
  }

  if (dst) {
    *dst = value;
  }

  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  union bit_cast {
    float fl;
    struct {
      uint32_t mantisse : 23;
      uint32_t exp : 8;
      uint32_t sgn : 1;
    };
  } float_cast = {.fl = src};

  int error = 0;
  int exp = float_cast.exp - 127;
  if (exp > 95) {
    error = 1;
    // } else if (exp < -94) {
    //   error = 1;
    //   if (dst) {
    //     s21_decimal temp = {0};
    //     *dst = temp;
    //   }
  } else {
    s21_decimal result = {{0}};
    s21_decimal add_value = {{0}};
    s21_decimal multiplier = {{5}};
    set_exp(&multiplier, 1);

    if (exp >= 0) {
      add_value.bits[exp / 32] |= (1 << (exp % 32));
    } else {
      add_value.bits[0] = 1;
      s21_decimal temp = {{10000000}};
      s21_mul(add_value, temp, &add_value);
      s21_mul(add_value, temp, &add_value);
      s21_mul(add_value, temp, &add_value);
      temp.bits[0] = 0;
      int t_exp = -exp;
      while (t_exp >= 95) {
        temp.bits[95 / 32] |= (1 << (95 % 32));
        s21_div(add_value, temp, &add_value);
        t_exp -= 95;
        temp.bits[2] = 0;
      }
      temp.bits[t_exp / 32] |= (1 << (t_exp % 32));
      s21_div(add_value, temp, &add_value);
    }

    result = add_value;
    //  print_decimal(result);
    uint32_t mantisse = (0U + float_cast.mantisse) << 9U;

    while (mantisse) {
      s21_mul(add_value, multiplier, &add_value);
      if (mantisse & 0x80000000U) {
        s21_add(result, add_value, &result);
      }
      mantisse <<= 1;
    }

    //  print_decimal(result);
    if (exp < 0) {
      s21_decimal temp = {{1}};
      set_exp(&temp, 21);
      s21_mul_extended(result, temp, &result, 0);
    }

    set_sgn(&result, float_cast.sgn);

    s21_big_decimal big_value;
    convert_to_big(result, &big_value);
    uint32_t digits_amount = big_log_10(big_value);
    if (digits_amount > 7) {
      uint32_t remainder = 0;
      big_value =
          big_div_ten_n_times_with_re(big_value, digits_amount - 8, NULL);
      big_value = big_div_ten_n_times_with_re(big_value, 1, &remainder);
      big_value = big_round(big_value, remainder, 5);
      big_value =
          big_mul_ten_n_times_with_re(big_value, digits_amount - 7, NULL);
    }

    if (dst) {
      convert_to_dec(big_value, dst, 0);
      if (is_null(*dst) && src != 0.0f && src != -0.0f) {
        error = 1;
      }
    }
  }

  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  s21_truncate(src, &src);
  if (((is_positive(src) && src.bits[0] >= 0x80000000U) ||
       (is_negative(src) && src.bits[0] > 0x80000000U)) ||
      src.bits[1] || src.bits[2]) {
    result = 1;
  }

  if (dst && result == 0) {
    *dst = (int)src.bits[0];
    if (is_negative(src) && src.bits[0] != 0x80000000) {
      *dst *= -1;
    }
  }

  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double result = 0.0;
  double power = 1.0;

  int exp = get_exp(src);
  for (int i = 0; i < exp; ++i) {
    power *= 0.1;
  }

  for (int i = 0; i < 96; ++i) {
    if (!!(src.bits[i / 32] & (1 << (i % 32)))) {
      result += power;
    }
    power *= 2.0;
  }

  if (dst) {
    *dst = (float)(result * (is_negative(src) ? -1.0 : 1.0));
  }

  return 0;
}
