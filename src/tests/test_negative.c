#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(test1) {
  s21_decimal val_1 = {{0}};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {{0}};
  set_sgn(&expect, 1);
  int error = s21_negate(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(get_sgn(res), 1);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test2) {
  s21_decimal val_1 = {0x41B65F28, 0x0B143885, 0x6582A536, 0};
  set_exp(&val_1, 28);
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0x41B65F28, 0x0B143885, 0x6582A536, 0};
  set_exp(&expect, 28);
  set_sgn(&expect, 1);
  int error = s21_negate(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(get_sgn(res), 1);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test3) {
  s21_decimal val_1 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  set_sgn(&expect, 1);
  int error = s21_negate(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(get_sgn(res), 1);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test4) {
  s21_decimal val_1 = {0x41B65F28, 0x0B143885, 0x6582A536, 0};
  set_exp(&val_1, 28);
  set_sgn(&val_1, 1);
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0x41B65F28, 0x0B143885, 0x6582A536, 0};
  set_exp(&expect, 28);
  set_sgn(&expect, 0);
  int error = s21_negate(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(get_sgn(res), 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test5) {
  s21_decimal val_1 = {0x41B65F28, 0x0B143885, 0x6582A536, 0};
  s21_decimal *res = NULL;
  int error = s21_negate(val_1, res);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite *suite_negate(void) {
  Suite *s = suite_create("negate");
  TCase *tc = tcase_create("negate_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);

  suite_add_tcase(s, tc);

  return s;
}