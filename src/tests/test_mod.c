#include "../s21_decimal.h"
#include "s21_tests.h"

START_TEST(mod_test_1) {
  int num1 = 3;
  int num2 = 2;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_2) {
  int num1 = -98765;
  int num2 = 1234;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_3) {
  int num1 = 30198;
  int num2 = 20210;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_4) {
  int num1 = -98765;
  int num2 = -1234;
  int res_origin = num1 % num2;
  // printf("%f", fmod(-98765, -1234));
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_5) {
  int num1 = 98765;
  int num2 = 127234;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_6) {
  int num1 = 342576;
  int num2 = -1542134;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mod_test_7) {
  int num1 = 0;
  int num2 = 1;
  int res_origin = num1 % num2;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mod(a, b, &res_dec);
  s21_decimal res;
  s21_from_int_to_decimal(0, &res);
  ck_assert_int_eq(res_int, res_origin);
  ck_assert_uint_eq(s21_is_equal(res_dec, res), 1);
}
END_TEST

START_TEST(mod_test_8) {
  s21_decimal dec1;
  s21_decimal dec2;
  float tmp1 = 1.2;
  float tmp2 = 0.25;
  float res_s21 = 0.0;
  float res = fmod(tmp1, tmp2);
  s21_from_float_to_decimal(tmp1, &dec1);
  s21_from_float_to_decimal(tmp2, &dec2);
  s21_decimal res1;
  s21_mod(dec1, dec2, &res1);
  s21_from_decimal_to_float(res1, &res_s21);
  ck_assert_float_eq_tol(res_s21, res, 6);
}
END_TEST

START_TEST(mod_test_9) {
  s21_decimal x = {{150000008, 21121212, 2112121212, 0}};
  s21_decimal y = {{23, 0, 0, 0}};
  s21_decimal true_var = {{0x1D26D188, 0x00000D1B, 0x00000000, 0x000C0000}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  set_exp(&x, 12);
  n1 = s21_mod(x, y, &z);
  // print_decimal(x);
  // print_decimal(y);
  // print_decimal(z);
  // print_decimal(true_var);
  ck_assert_uint_eq(s21_is_equal(true_var, z), 1);
}
END_TEST

START_TEST(mod_test_10) {
  s21_decimal x = {{0xFFFF, 21121212, 2112121212, 0}};
  s21_decimal y = {{11, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal true_var = {{0x00000002, 0x00000000, 0x00000000, 0x00170000}};
  int n1 = 0;
  set_exp(&y, 23);
  n1 = s21_mod(x, y, &z);
  //  print_decimal(x);
  //  print_decimal(y);
  //  print_decimal(z);
  //  print_decimal(true_var);
  ck_assert_uint_eq(s21_is_equal(true_var, z), 1);
}
END_TEST

START_TEST(mod_test_11) {
  s21_decimal x = {{0xFFFF, 21121212, 2112121212, 0}};
  s21_decimal y = {{0xFFFF112, 21121212, 2112122, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal true_var = {{0x903B42C1, 0x179872D9, 0x00203761, 0x00000000}};
  int n1 = 0;
  // print_decimal(x);
  // print_decimal(y);
  n1 = s21_mod(x, y, &z);
  ck_assert_uint_eq(s21_is_equal(true_var, z), 1);
}
END_TEST

START_TEST(mod_test_12) {
  s21_decimal x = {{11, 0, 0, 0}};
  s21_decimal y = {{0xFFFF, 21121212, 2112121212, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal true_var = {{0x0000000B, 0x00000000, 0x00000000, 0x00000000}};
  int n1 = 0;
  // print_decimal(x);
  // print_decimal(y);
  set_exp(&x, 23);
  set_exp(&true_var, 23);
  // print_decimal(x);
  // print_decimal(y);
  n1 = s21_mod(x, y, &z);
  ck_assert_uint_eq(s21_is_equal(true_var, z), 1);
}
END_TEST
Suite *suite_mod(void) {
  Suite *s = suite_create("mod");
  TCase *tc = tcase_create("mod_test");
  tcase_add_test(tc, mod_test_1);
  tcase_add_test(tc, mod_test_2);
  tcase_add_test(tc, mod_test_3);
  tcase_add_test(tc, mod_test_4);
  tcase_add_test(tc, mod_test_5);
  tcase_add_test(tc, mod_test_6);
  tcase_add_test(tc, mod_test_7);
  tcase_add_test(tc, mod_test_8);
  tcase_add_test(tc, mod_test_9);
  tcase_add_test(tc, mod_test_10);
  tcase_add_test(tc, mod_test_11);
  tcase_add_test(tc, mod_test_12);

  suite_add_tcase(s, tc);
  return s;
}