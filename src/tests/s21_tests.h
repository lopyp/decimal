#ifndef SRC_TESTS_S21_TESTS_H_
#define SRC_TESTS_S21_TESTS_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

Suite *suite_add(void);
Suite *suite_sub(void);
Suite *suite_mul(void);
Suite *suite_div(void);
Suite *suite_mod(void);

Suite *suite_compare(void);
Suite *suite_convert(void);

Suite *suite_from_decimal_to_int(void);
Suite *suite_from_decimal_to_float(void);
Suite *suite_from_float_to_decimal(void);
Suite *suite_from_int_to_decimal(void);

Suite *suite_floor(void);
Suite *suite_round(void);
Suite *suite_truncate(void);
Suite *suite_negate(void);

void run_tests(void);
void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_S21_TESTS_H_
