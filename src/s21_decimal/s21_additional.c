#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  if (result) {
    int exp = get_exp(value);
    if (exp > 0) {
      s21_big_decimal big_value;
      convert_to_big(value, &big_value);
      big_value = big_div_ten_n_times_with_re(big_value, exp, NULL);
      big_set_exp(&big_value, 0);
      convert_to_dec(big_value, result, 0);
    } else {
      *result = value;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  if (result) {
    int exp = get_exp(value);
    if (exp > 0) {
      s21_big_decimal big_value;
      convert_to_big(value, &big_value);
      big_value = big_div_ten_n_times_with_re(big_value, exp - 1, NULL);

      uint32_t digit = 0;
      big_value = big_div_ten_n_times_with_re(big_value, 1, &digit);
      big_set_exp(&big_value, 0);
      big_value = big_round(big_value, digit, 5);
      convert_to_dec(big_value, result, 0);
    } else {
      *result = value;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  if (result) {
    if (is_positive(value)) {
      s21_truncate(value, result);
    } else {
      s21_big_decimal big_value;
      convert_to_big(value, &big_value);
      big_value = strip_useless_nulls(big_value);
      int exp = big_get_exp(big_value);
      if (exp > 0) {
        big_value = big_div_ten_n_times_with_re(big_value, exp, NULL);
        big_set_exp(&big_value, 0);
        big_value = big_round(big_value, 0, 0);
      }
      convert_to_dec(big_value, result, 0);
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error_code = 0;
  if (result) {
    set_sgn(&value, get_sgn(value) ^ 1);
    *result = value;
  } else {
    error_code = 1;
  }
  return error_code;
}
