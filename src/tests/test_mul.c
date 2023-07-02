#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(test1) {
  s21_decimal val_1 = {{0}};
  s21_decimal val_2 = {{0}};
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {{0}};
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test2) {
  s21_decimal val_1 = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  s21_decimal val_2 = {0x10000000, 0x3E250261, 0x204FCE5E, 0};
  set_exp(&val_2, 28);
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test3) {
  s21_decimal val_1 = {0x41B65F28, 0x0B143885, 0x6582A536, 0};
  s21_decimal val_2 = {20, 0, 0, 0};
  set_exp(&val_1, 28);
  set_exp(&val_2, 1);
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x836CBE50, 0x1628710A, 0xCB054A6C, 0x001C0000};
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test4) {
  s21_decimal val_1 = {54655, 545, 0, 0};
  s21_decimal val_2 = {0, 0, 1, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x9999999A, 0xF9999999, 0x8B851EEE, 0x000E0000};
  set_exp(&val_1, 14);
  set_exp(&val_2, 3);
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test5) {
  s21_decimal val_1 = {54655, 545, 0, 0};
  s21_decimal val_2 = {0, 0, 1, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x9999999A, 0xF9999999, 0x8B851EEE, 0x800E0000};
  set_exp(&val_1, 14);
  set_exp(&val_2, 3);
  set_sgn(&val_1, 1);
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test6) {
  s21_decimal val_1 = {54655, 545, 0, 0};
  s21_decimal val_2 = {0, 0, 1, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0x9999999A, 0xF9999999, 0x8B851EEE, 0x000E0000};
  set_exp(&val_1, 14);
  set_exp(&val_2, 3);
  set_sgn(&val_1, 1);
  set_sgn(&val_2, 1);
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test7) {
  s21_decimal val_1 = {54655, 545, 5615641, 0};
  s21_decimal val_2 = {0, 0, 1, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 1);
  // ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test8) {
  s21_decimal val_1 = {1, 0, 0, 0};
  s21_decimal val_2 = {0, 18, 0, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0, 0, 0, 0};
  set_exp(&val_1, 28);
  set_exp(&val_2, 14);
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test9) {
  s21_decimal val_1 = {54655, 545, 5615641, 0};
  s21_decimal val_2 = {0, 0, 1, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  set_sgn(&val_2, 1);
  int error = s21_mul(val_1, val_2, &res);
  ck_assert_int_eq(error, 2);
  // ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

Suite *suite_mul(void) {
  Suite *s = suite_create("mul");
  TCase *tc = tcase_create("mul_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);
  tcase_add_test(tc, test7);
  tcase_add_test(tc, test8);
  tcase_add_test(tc, test9);

  suite_add_tcase(s, tc);

  return s;
}