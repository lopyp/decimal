#include "s21_tests.h"

START_TEST(test1) {
  s21_decimal val_1 = {{0}};
  s21_decimal val_2 = {{0}};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {{0}};
  int error = s21_sub(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

/*
  +184467440737095516165
  +110680464437962342410
  =73786976299133173755
*/

START_TEST(test2) {
  s21_decimal val_1 = {5, 0, 10, 0};
  s21_decimal val_2 = {10, 0xFFFFFFFFU, 5, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {3589934592, 999999998, 4000000000, 589824};
  set_exp(&val_1, 0);
  set_exp(&val_2, 0);
  set_sgn(&val_1, 0);
  set_sgn(&val_2, 0);
  int error = s21_sub(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

/*
  +184467440737095516165
  -110680464437962342410
  =295147905175057858575
*/

START_TEST(test3) {
  s21_decimal val_1 = {5, 0, 10, 0};
  s21_decimal val_2 = {10, 0xFFFFFFFFU, 5, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {1500000000, 4194967296, 1599999999, 524288};
  set_exp(&val_1, 0);
  set_exp(&val_2, 0);
  set_sgn(&val_1, 0);
  set_sgn(&val_2, 1);
  int error = s21_sub(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

/*
  -184467440737095516165
  -110680464437962342410
  =-295147905175057858575
*/

START_TEST(test4) {
  s21_decimal val_1 = {5, 0, 10, 0};
  s21_decimal val_2 = {10, 0xFFFFFFFFU, 5, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x0000000F, 0xFFFFFFFF, 0x0000000F, 0};
  set_sgn(&val_1, 1);
  set_sgn(&val_2, 0);
  set_sgn(&expect, 1);
  int error = s21_sub(val_1, val_2, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

/*
  +1.84467440737095516165
  -11068.046443796234241
  =11069.89111820360519616165
*/

START_TEST(test5) {
  s21_decimal val_1 = {5, 0, 10, 0};
  s21_decimal val_2 = {10, 0xFFFFFFFFU, 5, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0x000186A5, 0xFFFFD8F0, 0x0000EA69};
  set_exp(&val_1, 20);
  set_exp(&val_2, 16);
  set_exp(&expect, 20);
  set_sgn(&val_2, 1);
  // print_decimal(val_1);
  // print_decimal(val_2);
  int error = s21_sub(val_1, val_2, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

/*
  +7922816251426.4337593543950334
  +7922816251426.4337593543950335
  -0.0000000000000001
*/

START_TEST(test6) {
  s21_decimal val_1 = {0xFFFFFFFFU - 1, 0xFFFFFFFFU, 0xFFFFFFFFU, 0};
  s21_decimal val_2 = {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x1, 0, 0, 0x0};
  set_exp(&val_1, 16);
  set_exp(&val_2, 16);
  set_exp(&expect, 16);
  set_sgn(&expect, 1);
  // print_decimal(val_1);
  // print_decimal(val_2);
  int error = s21_sub(val_1, val_2, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

/*
  -7922816251426.4337593543950334
  +7922816251426.4337593543950335
  -15845632502852.867518708790067
*/

START_TEST(test7) {
  s21_decimal val_1 = {0xFFFFFFFFU - 1, 0xFFFFFFFFU, 0xFFFFFFFFU, 0};
  s21_decimal val_2 = {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0x33333333, 0x33333333, 0x33333333, 0x800F0000};
  set_exp(&val_1, 16);
  set_exp(&val_2, 16);
  set_sgn(&val_1, 1);
  set_sgn(&val_2, 0);
  // print_decimal(val_1);
  // print_decimal(val_2);
  int error = s21_sub(val_1, val_2, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST
/*
 ERROR
*/
START_TEST(test8) {
  s21_decimal val_1 = {0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0};
  s21_decimal val_2 = {5, 0, 0, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0xFFFFFFFFU - 1, 0xFFFFFFFFU, 0xFFFFFFFFU, 0};
  set_exp(&val_1, 0);
  set_exp(&val_2, 0);
  set_sgn(&val_1, 1);
  // set_sgn(&val_2, 0);
  // print_decimal(val_1);
  // print_decimal(val_2);
  int error = s21_sub(val_1, val_2, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(test9) {
  s21_decimal val_1 = {5, 0, 10, 0};
  s21_decimal val_2 = {10, 0xFFFFFFFFU, 0xFF, 0};
  s21_decimal res = {3456, 43234, 2134, 432};
  ;
  s21_decimal expect = {0x00000005, 0xFFFFFFFF, 0x000000F5, 0x00000000};
  set_sgn(&val_1, 1);
  set_sgn(&val_2, 1);
  set_sgn(&expect, 0);
  // print_decimal(val_1);
  // print_decimal(val_2);
  int error = s21_sub(val_1, val_2, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

Suite *suite_sub(void) {
  Suite *s = suite_create("sub");
  TCase *tc = tcase_create("sub_tc");

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