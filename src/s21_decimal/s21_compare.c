#include "../s21_decimal.h"

int positive_less(s21_big_decimal value_1, s21_big_decimal value_2) {
  int res = 1;
  for (int i = 6; i >= 0 && res; i--) {
    res = value_1.bits[i] >= value_2.bits[i];
    if (value_1.bits[i] > value_2.bits[i]) {
      break;
    }
  }
  return !res;
}

int is_both_zero(s21_big_decimal a, s21_big_decimal b) {
  return big_is_null(a) && big_is_null(b);
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  s21_big_decimal val_1_big = {{0}};
  s21_big_decimal val_2_big = {{0}};
  convert_to_big(value_1, &val_1_big);
  convert_to_big(value_2, &val_2_big);

  int sign1 = big_get_sgn(val_1_big);
  int sign2 = big_get_sgn(val_2_big);
  if (is_both_zero(val_1_big, val_2_big))
    res = 0;
  else if (sign1 != sign2)
    res = sign1;
  else {
    equalize(&val_1_big, &val_2_big);
    if (sign1) {
      big_set_sgn(&val_1_big, 0);
      big_set_sgn(&val_2_big, 0);
      res = positive_less(val_2_big, val_1_big);
    } else {
      res = positive_less(val_1_big, val_2_big);
    }
  }
  return res;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_2, value_1);
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2) && !s21_is_less(value_2, value_1);
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}
