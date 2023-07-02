#include "../s21_decimal.h"

int simp_add(s21_big_decimal value_1, s21_big_decimal value_2,
             s21_big_decimal *result) {
  int shift = 0;
  uint64_t res = 0;
  for (size_t i = 0; i < 7; i++) {
    res = (uint64_t)value_1.bits[i] + (uint64_t)value_2.bits[i] + shift;
    shift = res >> 32;
    result->bits[i] = res;
  }
  return shift;
}

void simp_sub(s21_big_decimal value_1, s21_big_decimal value_2,
              s21_big_decimal *result) {
  uint64_t shift = 0;
  for (size_t i = 0; i < 7; i++) {
    result->bits[i] = value_1.bits[i] - value_2.bits[i] - shift;
    if ((uint64_t)value_2.bits[i] + shift > (uint64_t)value_1.bits[i]) {
      shift = 1;
    } else {
      shift = 0;
    }
  }
}

void simp_mull(s21_big_decimal value_1, s21_big_decimal value_2,
               s21_big_decimal *result) {
  uint64_t res = 0;
  for (int i = 0; i < 7; i++) {
    uint64_t add_shift = 0;
    for (int j = 0; i + j < 7; j++) {
      res = (uint64_t)value_1.bits[i] * (uint64_t)value_2.bits[j] + add_shift;
      res += result->bits[i + j];
      add_shift = res >> 32;
      result->bits[i + j] = res;
    }
  }
}

int simp_div(s21_big_decimal value_1, s21_big_decimal value_2,
             s21_big_decimal *result, s21_big_decimal *remainder) {
  int error = 0;
  s21_big_decimal tmp = {{0}};
  *result = tmp;
  *remainder = tmp;
  if (big_is_null(value_2)) {
    error = 3;
  } else {
    for (int i = 6; i >= 0; i--) {
      *result = big_shift_decimal(*result);
      *remainder = big_shift_decimal(*remainder);
      remainder->bits[0] = value_1.bits[i];
      if (!positive_less(*remainder, value_2)) {
        uint64_t left = 0;
        uint64_t right = 0xFFFFFFFF;
        uint64_t mid = (left + right) / 2;
        while (left < right) {
          tmp = big_mul_uint_with_re(value_2, mid, NULL);
          if (positive_less(*remainder, tmp)) {
            right = mid - 1;
          } else {
            left = mid + 1;
          }
          mid = (left + right) / 2;
        }
        tmp = big_mul_uint_with_re(value_2, mid, NULL);
        if (positive_less(*remainder, tmp)) {
          mid -= 1;
          tmp = big_mul_uint_with_re(value_2, mid, NULL);
        }
        simp_sub(*remainder, tmp, remainder);
        result->bits[0] = mid;
      }
    }
  }
  return error;
}

int s21_mul_extended(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result, int bank_round) {
  int error = 0;

  s21_big_decimal val_1 = {{0}};
  s21_big_decimal val_2 = {{0}};
  s21_big_decimal res = {{0}};
  convert_to_big(value_1, &val_1);
  convert_to_big(value_2, &val_2);

  int sign_val_1 = get_sgn(value_1);
  int sign_val_2 = get_sgn(value_2);
  int exp_res = big_get_exp(val_1) + big_get_exp(val_2);

  if (sign_val_1 != sign_val_2) {
    big_set_sgn(&res, 1);
  }
  big_set_exp(&res, exp_res);
  simp_mull(val_1, val_2, &res);

  if (result) {
    error = convert_to_dec(res, result, bank_round);
  }

  return error;
}
