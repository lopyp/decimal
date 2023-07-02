#include "../s21_decimal.h"

#define INFO_BIT 7

int big_get_sgn(s21_big_decimal value) { return value.bits[INFO_BIT] >> 31U; }

// 0 - OK
// 1 - NOT OK
// 0 <= sgn <= 1
int big_set_sgn(s21_big_decimal *value, int sgn) {
  int result = sgn >= 0 && sgn <= 1;
  if (value == NULL) {
    result = 0;
  }

  if (result) {
    value->bits[INFO_BIT] &= ~SGN_BIT;
    value->bits[INFO_BIT] |= (uint32_t)sgn << 31U;
  }

  return !result;
}

int big_get_exp(s21_big_decimal value) {
  return (value.bits[INFO_BIT] & EXP_BITS) >> 16U;
}

// 0 - OK
// 1 - NOT OK
// 0 <= exp <= 60
int big_set_exp(s21_big_decimal *value, int exp) {
  int result = exp >= 0 && exp <= 60;
  if (value == NULL) {
    result = 0;
  }

  if (result) {
    value->bits[INFO_BIT] &= ~EXP_BITS;
    value->bits[INFO_BIT] |= exp << 16;
  }

  return !result;
}

int big_is_null(s21_big_decimal val) {
  int flag = 1;
  for (int i = 0; i <= 6; ++i) {
    flag = flag && (val.bits[i] == 0);
  }

  return flag;
}

void equalize(s21_big_decimal *a, s21_big_decimal *b) {
  int e1 = big_get_exp(*a);
  int e2 = big_get_exp(*b);
  int big_e = e1 > e2 ? e1 : e2;
  int small_e = e1 < e2 ? e1 : e2;
  s21_big_decimal *curr = e1 > e2 ? b : a;
  *curr = big_mul_ten_n_times_with_re(*curr, big_e - small_e, NULL);
  big_set_exp(curr, big_e);
}

#if defined(DEBUG)

#include <stdio.h>

// obsolete
s21_big_decimal big_div_10_with_re(s21_big_decimal val, int *remainder) {
  return big_div_uint_with_re(val, 10, remainder);
}

// obsolete
s21_big_decimal big_mul_10_with_re(s21_big_decimal val, int *remainder) {
  return big_mul_uint_with_re(val, 10, remainder);
}

void print_big_decimal(s21_big_decimal val) {
  int exp = big_get_exp(val);

  if (big_is_null(val)) {
    printf("%c0.0", big_is_negative(val) ? '-' : '+');
  } else {
    char buff[100] = {'\0'};
    int digit = 0;
    int pos = 0;
    while (!big_is_null(val)) {
      if (pos == exp && exp > 0) {
        buff[pos] = '.';
        pos++;
      }
      val = big_div_10_with_re(val, &digit);
      buff[pos] = '0' + digit;
      pos++;
    }

    if (pos <= exp && exp > 0) {
      while (pos < exp) {
        buff[pos] = '0';
        pos++;
      }

      buff[pos] = '.';
      pos++;
    }

    if (buff[pos - 1] == '.') {
      buff[pos] = '0';
      pos++;
    }
    buff[pos] = big_is_negative(val) ? '-' : '+';
    for (int i = pos; i >= 0; --i) {
      putchar(buff[i]);
    }
  }
}

void print_decimal(s21_decimal val) {
  s21_big_decimal tmp;
  convert_to_big(val, &tmp);
  print_big_decimal(tmp);
  printf("\n");
}

#endif  // __DEBUG__
