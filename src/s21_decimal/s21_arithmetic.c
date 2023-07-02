#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_big_decimal val_1 = {{0}};
  s21_big_decimal val_2 = {{0}};
  convert_to_big(value_1, &val_1);
  convert_to_big(value_2, &val_2);

  int sign_val_1 = get_sgn(value_1);
  int sign_val_2 = get_sgn(value_2);

  equalize(&val_1, &val_2);

  if (sign_val_1 == sign_val_2) {
    simp_add(val_1, val_2, &val_1);  // val1 -> res
  } else {
    set_sgn(&value_1, 0);
    set_sgn(&value_2, 0);
    if (s21_is_greater_or_equal(value_1, value_2)) {
      simp_sub(val_1, val_2, &val_1);  // val1 -> res
    } else {
      simp_sub(val_2, val_1, &val_1);
      big_set_sgn(&val_1, sign_val_2);  // val2 -> res
    }
  }

  if (result) {
    error = convert_to_dec(val_1, result, 1);
  }

  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_big_decimal val_1 = {{0}};
  s21_big_decimal val_2 = {{0}};
  convert_to_big(value_1, &val_1);
  convert_to_big(value_2, &val_2);

  int sign_val_1 = get_sgn(value_1);
  int sign_val_2 = get_sgn(value_2);

  equalize(&val_1, &val_2);

  if (sign_val_1 == sign_val_2) {
    set_sgn(&value_1, 0);
    set_sgn(&value_2, 0);
    if (s21_is_greater_or_equal(value_1, value_2)) {
      simp_sub(val_1, val_2, &val_1);  // val1 -> res
    } else {
      simp_sub(val_2, val_1, &val_1);
      if (sign_val_2 == 0)
        big_set_sgn(&val_1, 1);
      else
        big_set_sgn(&val_1, 0);
    }
  } else if (sign_val_2 == 1) {
    simp_add(val_1, val_2, &val_1);
  } else if (sign_val_1 == 1) {
    simp_add(val_1, val_2, &val_1);
  }

  if (result) {
    error = convert_to_dec(val_1, result, 1);
  }

  return error;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  error = s21_mul_extended(value_1, value_2, result, 1);

  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_big_decimal val_1 = {{0}};
  s21_big_decimal val_2 = {{0}};
  s21_big_decimal res = {{0}};
  s21_big_decimal rem = {{0}};
  s21_big_decimal rem2 = {{0}};
  convert_to_big(value_1, &val_1);
  convert_to_big(value_2, &val_2);

  int sign_val_1 = get_sgn(value_1);
  int sign_val_2 = get_sgn(value_2);
  int exp_res = big_get_exp(val_1) - big_get_exp(val_2);

  if (exp_res < 0) {
    val_1 = big_mul_ten_n_times_with_re(val_1, -exp_res, NULL);
    exp_res = 0;
  }
  error = simp_div(val_1, val_2, &res, &rem);
  big_set_exp(&res, exp_res);
  if (!big_is_null(rem)) {
    rem = big_mul_ten_n_times_with_re(rem, 29, NULL);
    simp_div(rem, val_2, &rem, &rem2);
    big_set_exp(&rem, 29 + exp_res);
  }

  equalize(&res, &rem);
  simp_add(res, rem, &res);
  if (result && error == 0) {
    error = convert_to_dec(res, result, 1);
    if (sign_val_1 != sign_val_2) {
      set_sgn(result, 1);
    }
  }

  return error;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  s21_big_decimal val_1 = {{0}};
  s21_big_decimal val_2 = {{0}};
  s21_big_decimal res = {{0}};
  s21_big_decimal rem = {{0}};
  convert_to_big(value_1, &val_1);
  convert_to_big(value_2, &val_2);

  int sign_val_1 = get_sgn(value_1);
  int exp_res = big_get_exp(val_1) - big_get_exp(val_2);

  if (exp_res < 0) {
    val_1 = big_mul_ten_n_times_with_re(val_1, -exp_res, NULL);
    exp_res = 0;
  } else {
    equalize(&val_1, &val_2);
  }
  error = simp_div(val_1, val_2, &res, &rem);
  big_set_sgn(&rem, sign_val_1);
  big_set_exp(&rem, big_get_exp(val_2));

  if (result && error == 0) {
    error = convert_to_dec(rem, result, 1);
  }

  return error;
}
