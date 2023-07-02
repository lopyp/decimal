#ifndef SRC_S21_EXTRA_DECIMAL_H_
#define SRC_S21_EXTRA_DECIMAL_H_

#include "s21_decimal.h"

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;


/*
  additional
*/

int get_sgn(s21_decimal value);
int set_sgn(s21_decimal *value, int sgn);
int get_exp(s21_decimal value);
int set_exp(s21_decimal *value, int exp);

#define big_is_negative(X) (big_get_sgn(X))
#define is_negative(X) (get_sgn(X))

int is_null(s21_decimal val);

// big_dec

s21_big_decimal big_round(s21_big_decimal value, uint32_t digit, uint32_t cmp_digit);

int convert_to_big(s21_decimal, s21_big_decimal *);
int convert_to_dec(s21_big_decimal, s21_decimal *, int round_mod);

int big_get_sgn(s21_big_decimal value);
int big_set_sgn(s21_big_decimal *value, int sgn);
int big_get_exp(s21_big_decimal value);
int big_set_exp(s21_big_decimal *value, int exp);

int big_get_bit(s21_big_decimal n, int pos);
void big_set_bit(s21_big_decimal *n, int pos, int val);

// @sarellad
// done

// big shift decimal
s21_big_decimal big_shift_decimal(s21_big_decimal val);

// !!!obsolete!!!
s21_big_decimal big_div_10_with_re(s21_big_decimal val, int *remainder);
// !!!obsolete!!!
s21_big_decimal big_mul_10_with_re(s21_big_decimal val, int *remainder);

s21_big_decimal big_div_uint_with_re(s21_big_decimal val, uint32_t divider,
                                     uint32_t *remainder);
s21_big_decimal big_mul_uint_with_re(s21_big_decimal val, uint32_t multiplier,
                                     uint32_t *remainder);

// !!!not safe!!!
// remainder is right, if n <= 4
// use big_log_10 before
s21_big_decimal big_mul_ten_n_times_with_re(s21_big_decimal val, uint32_t n,
                                            uint32_t *remainder);

// !!!not safe!!!
// remainder is right, if n <= 4
// use big_log_10 before
s21_big_decimal big_div_ten_n_times_with_re(s21_big_decimal val, uint32_t n,
                                            uint32_t *remainder);

uint32_t big_log_10(s21_big_decimal val);
s21_big_decimal strip_useless_nulls(s21_big_decimal val);

void print_big_decimal(s21_big_decimal val);

void print_decimal(s21_decimal val);

// @donnette
int simp_add(s21_big_decimal value_1, s21_big_decimal value_2,
             s21_big_decimal *result);
void simp_sub(s21_big_decimal value_1, s21_big_decimal value_2,
              s21_big_decimal *result);
void simp_mull(s21_big_decimal value_1, s21_big_decimal value_2,
               s21_big_decimal *result);
int simp_div(s21_big_decimal value_1, s21_big_decimal value_2, s21_big_decimal *result, s21_big_decimal *remainder);
void equalize(s21_big_decimal *a, s21_big_decimal *b);
int positive_less(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_mul_extended(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int bank_round);

#define big_is_positive(X) (!(big_is_negative(X)))
#define is_positive(X) (!(is_negative(X)))

int big_is_null(s21_big_decimal val);

#endif  //  SRC_S21_EXTRA_DECIMAL_H_