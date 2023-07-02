#include "s21_tests.h"

START_TEST(test1) {
  // 2 max dec
  s21_decimal a = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  s21_decimal b = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_equal(b, a), 1);
  ck_assert_int_eq(s21_is_not_equal(b, a), 0);
}
END_TEST

START_TEST(test2) {
  // 2 0
  s21_decimal a = {0, 0, 0, 0};
  s21_decimal b = {0, 0, 0, 0};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_equal(b, a), 1);
  ck_assert_int_eq(s21_is_not_equal(b, a), 0);
}
END_TEST

START_TEST(test3) {
  // 2 0 but exp
  s21_decimal a = {0, 0, 0, 0};
  s21_decimal b = {0, 0, 0, 0};
  set_exp(&a, 23);
  set_exp(&b, 23);
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
  ck_assert_int_eq(s21_is_less(b, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_equal(b, a), 1);
  ck_assert_int_eq(s21_is_not_equal(b, a), 0);
}
END_TEST

START_TEST(test4) {
  // rand dec
  s21_decimal a = {743895734, 353234, 234045, 0};
  s21_decimal b = {74389534, 353234, 134045, 0};
  set_exp(&a, 23);
  set_exp(&b, 23);
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 0);
  ck_assert_int_eq(s21_is_equal(b, a), 0);
  ck_assert_int_eq(s21_is_not_equal(b, a), 1);
}
END_TEST

START_TEST(test5) {
  // rand dec exp only
  s21_decimal a = {743895734, 353234, 0, 0};
  s21_decimal b = {74389534, 353234, 0, 0};
  set_exp(&a, 23);
  set_exp(&b, 23);
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 0);
  ck_assert_int_eq(s21_is_equal(b, a), 0);
  ck_assert_int_eq(s21_is_not_equal(b, a), 1);
}
END_TEST

START_TEST(test6) {
  // rand negative dec
  s21_decimal a = {743895734, 353234, 234045, 0};
  s21_decimal b = {74389534, 353234, 134045, 0};
  set_exp(&a, 23);
  set_exp(&b, 23);
  set_sgn(&a, 1);
  set_sgn(&b, 1);
  // s21_big_decimal val;
  // convert_to_big(a, &val);
  // print_big_decimal(val);
  // printf("\n");
  // convert_to_big(b, &val);
  // print_big_decimal(val);
  // printf("\n");
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
  ck_assert_int_eq(s21_is_greater(b, a), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_equal(b, a), 0);
  ck_assert_int_eq(s21_is_not_equal(b, a), 1);
}
END_TEST

START_TEST(test7) {
  // rand dec exp only
  s21_decimal a = {743895734, 353234, 0, 0};
  s21_decimal b = {74389534, 353234, 0, 0};
  set_exp(&a, 23);
  set_exp(&b, 23);
  set_sgn(&a, 1);
  set_sgn(&b, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
  ck_assert_int_eq(s21_is_greater(b, a), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_equal(b, a), 0);
  ck_assert_int_eq(s21_is_not_equal(b, a), 1);
}
END_TEST

START_TEST(test8) {
  // rand +- dec
  s21_decimal a = {743895734, 353234, 234045, 0};
  s21_decimal b = {74389534, 353234, 134045, 0};
  set_exp(&a, 23);
  set_exp(&b, 23);
  set_sgn(&a, 1);
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 0);
  ck_assert_int_eq(s21_is_greater(b, a), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
  ck_assert_int_eq(s21_is_equal(b, a), 0);
  ck_assert_int_eq(s21_is_not_equal(b, a), 1);
}
END_TEST

Suite *suite_compare(void) {
  Suite *s = suite_create("suite_compare");
  TCase *tc = tcase_create("compare_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);
  tcase_add_test(tc, test7);
  tcase_add_test(tc, test8);
  suite_add_tcase(s, tc);

  return s;
}