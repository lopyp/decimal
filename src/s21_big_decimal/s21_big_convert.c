#include "../s21_decimal.h"

int convert_to_big(s21_decimal src, s21_big_decimal* dst) {
  s21_big_decimal val = {{0}};

  val.bits[0] = src.bits[0];
  val.bits[1] = src.bits[1];
  val.bits[2] = src.bits[2];

  big_set_sgn(&val, get_sgn(src));
  big_set_exp(&val, get_exp(src));

  val = strip_useless_nulls(val);

  if (dst) {
    *dst = val;
  }

  return 0;
}

// 0 - OK
// 1 - ERROR: TOO BIG
// 2 - ERROR: TOO SMALL
// round_mod == 0 --> mathemathical rounding
// round_mod == 1 --> banking rounding
int convert_to_dec(s21_big_decimal src, s21_decimal* dst, int round_mod) {
  int result = 0;
  int exp = big_get_exp(src);
  int sgn = big_get_sgn(src);
  uint32_t remainder = 0;

  while (exp > 28) {
    src = big_div_ten_n_times_with_re(src, 1, &remainder);
    --exp;
  }

  int digit_amount = big_log_10(src);
  while (exp > 0 && (digit_amount > 29 || src.bits[3] != 0)) {
    src = big_div_ten_n_times_with_re(src, 1, &remainder);
    --exp;
    --digit_amount;
  }

  if (src.bits[0] & 1 || round_mod == 0) {
    src = big_round(src, remainder, 5);
  } else {
    src = big_round(src, remainder, 6);
  }

  if (exp > 0 && src.bits[3] != 0) {
    src = big_div_ten_n_times_with_re(src, 1, NULL);
    --exp;
  }

  big_set_exp(&src, exp);
  src = strip_useless_nulls(src);
  exp = big_get_exp(src);

  if (exp == 0 && (digit_amount > 29 || src.bits[3] != 0)) {
    result = 1;
    if (sgn) {
      result = 2;
    }
  } else {
    s21_decimal val = {{src.bits[0], src.bits[1], src.bits[2]}};
    set_exp(&val, exp);
    set_sgn(&val, big_get_sgn(src));
    if (dst) {
      *dst = val;
    }
  }

  return result;
}
