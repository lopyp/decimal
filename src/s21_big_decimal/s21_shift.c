#include "../s21_decimal.h"

static s21_big_decimal strip_nx_useless_nulls(s21_big_decimal val, int x);

s21_big_decimal big_div_uint_with_re(s21_big_decimal val, uint32_t divider,
                                     uint32_t *remainder) {
  uint64_t re = 0;
  for (int i = 6; i >= 0; --i) {
    uint64_t next_re = 0;
    re = (re << 32) + val.bits[i];
    next_re = re % divider;
    val.bits[i] = re / divider;
    re = next_re;
  }

  if (remainder) {
    *remainder = re;
  }

  return val;
}

s21_big_decimal big_mul_uint_with_re(s21_big_decimal val, uint32_t multiplier,
                                     uint32_t *remainder) {
  uint64_t mul_res = 0;
  for (int i = 0; i <= 6; ++i) {
    mul_res = (uint64_t)multiplier * val.bits[i] + (mul_res >> 32U);
    val.bits[i] = mul_res & 0xFFFFFFFFU;
  }

  if (remainder) {
    *remainder = mul_res >> 32U;
  }

  return val;
}

// !!!not safe!!!
// remainder is right, if n <= 4
s21_big_decimal big_mul_ten_n_times_with_re(s21_big_decimal val, uint32_t n,
                                            uint32_t *remainder) {
  for (int i = 0, end = n / 4; i < end; ++i) {
    val = big_mul_uint_with_re(val, 10000, remainder);
  }

  uint32_t multiplier = 1;
  for (int i = 0, end = n % 4; i < end; ++i) {
    multiplier *= 10;
  }

  if (multiplier > 1) {
    val = big_mul_uint_with_re(val, multiplier, remainder);
  }

  return val;
}

// !!!not safe!!!
// remainder is right, if n <= 4
s21_big_decimal big_div_ten_n_times_with_re(s21_big_decimal val, uint32_t n,
                                            uint32_t *remainder) {
  for (int i = 0, end = n / 4; i < end; ++i) {
    val = big_div_uint_with_re(val, 10000, remainder);
  }

  uint32_t divider = 1;
  for (int i = 0, end = n % 4; i < end; ++i) {
    divider *= 10;
  }

  if (divider > 1) {
    val = big_div_uint_with_re(val, divider, remainder);
  }

  return val;
}

uint32_t big_log_10(s21_big_decimal val) {
  uint32_t result = 0;
  uint32_t re = 0;
  s21_big_decimal next_val = big_div_ten_n_times_with_re(val, 4, &re);
  while (!big_is_null(next_val)) {
    result += 4;
    next_val = big_div_ten_n_times_with_re(next_val, 4, &re);
  }

  while (re > 0) {
    re /= 10;
    result += 1;
  }

  return result;
}

// strip n * x useless nulls, where x belong N
static s21_big_decimal strip_nx_useless_nulls(s21_big_decimal val, int x) {
  int exp = big_get_exp(val);
  uint32_t re = 0;
  s21_big_decimal next_val;

  next_val = big_div_ten_n_times_with_re(val, x, &re);
  while (exp >= x && re == 0) {
    exp -= x;
    val = next_val;
    next_val = big_div_ten_n_times_with_re(next_val, x, &re);
  }

  big_set_exp(&val, exp);

  return val;
}

s21_big_decimal strip_useless_nulls(s21_big_decimal val) {
  val = strip_nx_useless_nulls(val, 4);
  val = strip_nx_useless_nulls(val, 1);

  return val;
}

s21_big_decimal big_shift_decimal(s21_big_decimal val) {
  for (size_t i = 6; i > 0; i--) {
    val.bits[i] = val.bits[i - 1];
  }
  val.bits[0] = 0;
  return val;
}