#include "../s21_decimal.h"

s21_big_decimal big_round(s21_big_decimal value, uint32_t digit,
                          uint32_t cmp_digit) {
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};

  if (digit >= cmp_digit) {
    simp_add(value, one, &value);
  }

  return value;
}