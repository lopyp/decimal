#include "../s21_decimal.h"

#define INFO_BIT 3

int get_sgn(s21_decimal value) { return value.bits[3] >> 31U; }

// 0 - OK
// 1 - NOT OK
int set_sgn(s21_decimal* value, int sgn) {
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

int get_exp(s21_decimal value) {
  return (value.bits[INFO_BIT] & EXP_BITS) >> 16U;
}

// 0 - OK
// 1 - NOT OK
int set_exp(s21_decimal* value, int exp) {
  int result = exp >= 0 && exp <= 28;
  if (value == NULL) {
    result = 0;
  }

  if (result) {
    value->bits[INFO_BIT] &= ~EXP_BITS;
    value->bits[INFO_BIT] |= exp << 16;
  }

  return !result;
}

int is_null(s21_decimal val) {
  int flag = 1;
  for (int i = 0; i <= 2; ++i) {
    flag = flag && (val.bits[i] == 0);
  }

  return flag;
}
