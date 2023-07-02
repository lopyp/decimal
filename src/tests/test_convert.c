#include <limits.h>

#include "../s21_decimal.h"
#include "s21_tests.h"

// int -> dec

START_TEST(test1) {
  int val_1 = INT_MAX;
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {INT_MAX, 0, 0, 0};
  int error = s21_from_int_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test2) {
  int val_1 = INT_MIN;
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {2147483648, 0, 0, 0};
  set_sgn(&expect, 1);
  int error = s21_from_int_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test3) {
  int val_1 = 154845;
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {154845, 0, 0, 0};
  int error = s21_from_int_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test4) {
  int val_1 = -154845;
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {154845, 0, 0, 0};
  set_sgn(&expect, 1);
  int error = s21_from_int_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

// dec -> int

START_TEST(test5) {
  int val_1 = INT_MAX;
  s21_decimal expect = {INT_MAX, 0, 0, 0};
  int error = s21_from_decimal_to_int(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(val_1, INT_MAX);
}
END_TEST

START_TEST(test6) {
  int val_1 = INT_MIN;

  s21_decimal expect = {2147483648, 0, 0, 0};
  set_sgn(&expect, 1);
  int error = s21_from_decimal_to_int(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(val_1, INT_MIN);
}
END_TEST

START_TEST(test7) {
  int val_1 = 154845;
  s21_decimal expect = {154845, 0, 0, 0};
  int error = s21_from_decimal_to_int(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(val_1, 154845);
}
END_TEST

START_TEST(test8) {
  int val_1 = -154845;
  s21_decimal expect = {154845, 0, 0, 0};
  set_sgn(&expect, 1);
  int error = s21_from_decimal_to_int(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(val_1, -154845);
}
END_TEST

// dec -> float

START_TEST(test9) {
  float val_1 = -154845.;
  s21_decimal expect = {154845, 0, 0, 0};
  set_sgn(&expect, 1);
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(val_1, -154845.);
}
END_TEST

START_TEST(test10) {
  float val_1 = -15484.5;
  s21_decimal expect = {154845, 0, 0, 0};
  set_sgn(&expect, 1);
  set_exp(&expect, 1);
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(val_1, -15484.5);
}
END_TEST

START_TEST(test11) {
  float val_1 = (float)-79228162514264.337593543950335;
  s21_decimal expect = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  set_sgn(&expect, 1);
  set_exp(&expect, 15);
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(val_1, -79228162801664.);
}
END_TEST

START_TEST(test12) {
  float val_1 = (float)-79228162514264.337593543950335;
  s21_decimal expect = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  set_exp(&expect, 25);
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(val_1, 7922.81640625);
}
END_TEST

START_TEST(test13) {
  float val_1 = (float)-79228162514264.337593543950335;
  s21_decimal expect = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  set_exp(&expect, 25);
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(val_1, 7922.81640625);
}
END_TEST

START_TEST(test14) {
  float val_1 = (float)-79228162514264.337593543950335;
  s21_decimal expect = {0xFFFFFFFF, 0xFFFFFFFF, 0, 0};
  set_exp(&expect, 25);
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(val_1, (float)0.0000018446744434186257421970367431640625);
}
END_TEST

START_TEST(test15) {
  float val_1 = (float)-79228162514264.337593543950335;
  s21_decimal expect = {0xFFFFFFFF, 418458, 0, 0};
  set_exp(&expect, 25);
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(
      val_1, (float)1.7972677512911872099721222184598445892333984375E-10);
}
END_TEST

START_TEST(test16) {
  float val_1 = (float)-79228162514264.337593543950335;
  s21_decimal expect = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  int error = s21_from_decimal_to_float(expect, &val_1);
  ck_assert_int_eq(error, 0);
  ck_assert_float_eq(val_1, (float)79228162514264337593543950336.);
}
END_TEST

// float -> dec

START_TEST(test17) {
  float val_1 = 1542184.87846595;
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x00178829, 0x00000000, 0x00000000, 0x0000000};
  int error = s21_from_float_to_decimal(val_1, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test18) {
  float val_1 = -1542184.87846595;
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x00178829, 0x00000000, 0x00000000, 0x80000000};
  int error = s21_from_float_to_decimal(val_1, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test19) {
  float val_1 = 0.01;
  s21_decimal res = {3456, 43234, 2134, 432};
  s21_decimal expect = {0x00000001, 0x00000000, 0x00000000, 0x00020000};
  int error = s21_from_float_to_decimal(val_1, &res);
  // print_decimal(res);
  // print_decimal(expect);
  ck_assert_int_eq(error, 0);
  ck_assert_uint_eq(s21_is_equal(expect, res), 1);
}
END_TEST

START_TEST(test20) {
  float val_1 = 79228162514264337593543950336.;
  s21_decimal res = {3456, 43234, 2134, 432};
  int error = s21_from_float_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test21) {
  float val_1 = 79228162514264337593543950335.;
  s21_decimal res = {3456, 43234, 2134, 432};
  int error = s21_from_float_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test22) {
  float val_1 = 0. / 0.;
  s21_decimal res = {3456, 43234, 2134, 432};
  int error = s21_from_float_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test23) {
  float val_1 = 1. / 0.;
  s21_decimal res = {3456, 43234, 2134, 432};
  int error = s21_from_float_to_decimal(val_1, &res);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test24) {
  float val_1 = 4e-29F;
  s21_decimal val_2 = {{0}};
  int error = s21_from_float_to_decimal(val_1, &val_2);
  s21_decimal exp = {{0}};
  ck_assert_int_eq(s21_is_equal(exp, val_2), 1);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test25) {
  float val_1 = 5e-29F;
  s21_decimal val_2 = {{0}};
  int error = s21_from_float_to_decimal(val_1, &val_2);
  s21_decimal exp = {{0x00000001, 0x00000000, 0x00000000, 0x001C0000}};

  ck_assert_int_eq(s21_is_equal(exp, val_2), 1);
}
END_TEST

START_TEST(test26) {
  float val_1 = 1e-29F;
  s21_decimal val_2 = {{0}};
  int error = s21_from_float_to_decimal(val_1, &val_2);
  s21_decimal exp = {{0x00000000, 0x00000000, 0x00000000, 0x001C0000}};
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(s21_is_equal(exp, val_2), 1);
}
END_TEST

START_TEST(test27) {
  int mix = INT_MIN;
  // float val_1 = 1e-29F;
  s21_decimal val_2 = {{0}};
  int error = s21_from_int_to_decimal(mix, &val_2);
  // print_decimal(val_2);
  // printf("##########");
  s21_decimal exp = {{0x80000000, 0x00000000, 0x00000000, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(exp, val_2), 1);
}
END_TEST

START_TEST(test28) {
  int res = 0;
  s21_decimal val_1 = {{0xB2D05E00, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal val_2 = {{0xB2D05E00, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal val_3 = {{3000000000, 0x00000000, 0x00000000, 0x80000000}};
  int error = s21_from_decimal_to_int(val_1, &res);
  int error1 = s21_from_decimal_to_int(val_2, &res);
  int error2 = s21_from_decimal_to_int(val_3, &res);

  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(error1, 1);
  ck_assert_int_eq(error2, 1);
}
END_TEST
START_TEST(test29) {
  int res_int = 300000;
  int res = 0;
  s21_decimal val_1 = {{0x000493E0, 0x00000000, 0x00000000, 0x00000000}};
  int error = s21_from_decimal_to_int(val_1, &res);
  ck_assert_int_eq(error, 0);
  ck_assert_int_eq(res, res_int);
}
END_TEST

Suite *suite_convert(void) {
  Suite *s = suite_create("convert");
  TCase *tc = tcase_create("convert_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);
  tcase_add_test(tc, test7);
  tcase_add_test(tc, test8);
  tcase_add_test(tc, test9);
  tcase_add_test(tc, test10);
  tcase_add_test(tc, test11);
  tcase_add_test(tc, test12);
  tcase_add_test(tc, test13);
  tcase_add_test(tc, test14);
  tcase_add_test(tc, test15);
  tcase_add_test(tc, test16);
  tcase_add_test(tc, test17);
  tcase_add_test(tc, test18);
  tcase_add_test(tc, test19);
  tcase_add_test(tc, test20);
  tcase_add_test(tc, test21);
  tcase_add_test(tc, test22);
  tcase_add_test(tc, test23);
  tcase_add_test(tc, test21);
  tcase_add_test(tc, test22);
  tcase_add_test(tc, test24);
  tcase_add_test(tc, test25);
  tcase_add_test(tc, test26);
  tcase_add_test(tc, test27);
  tcase_add_test(tc, test28);
  tcase_add_test(tc, test29);

  suite_add_tcase(s, tc);

  return s;
}