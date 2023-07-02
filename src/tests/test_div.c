#include "s21_tests.h"

START_TEST(div_1) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "3100000000 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(div_2) {
  s21_decimal x = {{1, 0, 0, 0}};
  s21_decimal y = {{3100000000, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};

  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "1854727994 751066592 0 1835008";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(div_3) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_4) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_5) {
  s21_decimal x = {{52525252, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};

  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_6) {
  s21_decimal x = {{52525252, 0, 0, 8845}};
  s21_decimal y = {{0, 0, 0, 10}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_7) {
  s21_decimal x = {{52525252, 0, 0, 65465}};
  s21_decimal y = {{0, 0, 0, 9598595}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_8) {
  int num1 = 1;
  int num2 = -1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal expect = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_from_int_to_decimal(-1, &expect);
  int n1 = 0;
  n1 = s21_div(a, b, &z);
  ck_assert_uint_eq(s21_is_equal(expect, z), 1);
}
END_TEST

START_TEST(div_13) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};

  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(div_14) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = 0;
  n1 = s21_div(x, y, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 3);
}
END_TEST

START_TEST(div_15) {
  s21_decimal x = {{5, 0, 0, 0}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_div(x, y, &z);
  char res1[1000], res2[1000] = "1 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(div_exp) {
  s21_decimal a = {0x00000241, 0, 0, 0};
  s21_decimal b = {25, 0, 0, 0};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal expect = {{2308, 0, 0, 0}};

  set_exp(&a, 0);
  set_exp(&b, 2);
  s21_div(a, b, &z);
  ck_assert_uint_eq(s21_is_equal(z, expect), 1);
}
END_TEST

START_TEST(div_16) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -16384;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_div(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(div_17) {
  int num1 = 1;
  int num2 = 128;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0x0001312D, 0x00000000, 0x00000000, 0x00070000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_18) {
  int num1 = 0;
  int num2 = 128;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_19) {
  int num1 = 1;
  int num2 = 7;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0x94924924, 0x5205497B, 0x049DAFC4, 0x001C0000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_20) {
  int num1 = 2;
  int num2 = 7;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0x29249249, 0xA40A92F7, 0x093B5F88, 0x001C0000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_21) {
  int num1 = 3;
  int num2 = 7;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0xBDB6DB6E, 0xF60FDC72, 0x0DD90F4C, 0x001C0000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_22) {
  float num1 = 0.1;
  float num2 = 0.000000000000001;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0x107A4000, 0x00005AF3, 0x00000000, 0x00000000}};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_23) {
  float num1 = -0.11;
  float num2 = -0.000000000000002;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0xAF767000, 0x00003205, 0x00000000, 0x00000000}};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_24) {
  float num1 = -0.12345;
  float num2 = -0.123456;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0x83D7FCD1, 0xF61AAE4F, 0x204F6773, 0x001C0000}};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_25) {
  float num1 = -123456.1;
  float num2 = -123456.1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0x00000001, 0x00000000, 0x00000000, 0x00000000};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}

START_TEST(div_26) {
  float num1 = 123456.1;
  float num2 = 123456.1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {0x00000001, 0x00000000, 0x00000000, 0x00000000};
  s21_from_float_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);

  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_27) {
  int num1 = 1;
  float num2 = 123456.1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0xE666C1CA, 0x0B18A003, 0x00001127, 0x001C0000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_28) {
  int num1 = 3;
  float num2 = 123456.1;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0xB334455F, 0x2149E00B, 0x00003375, 0x001C0000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_29) {
  int num1 = 3;
  float num2 = 0.000011;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0xCE8BA2E9, 0xEF4DA965, 0x581F78A3, 0x00170000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_30) {
  int num1 = 11111112;
  float num2 = 0.000011;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_decimal res = {{0xCBD1745D, 0x98C85B1B, 0x20A35C42, 0x00100000}};
  s21_from_int_to_decimal(num1, &a);
  s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_31) {
  int num1 = 11111112;
  s21_decimal a = {0};
  s21_decimal b = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  s21_decimal res = {{0x00156633, 0x00000000, 0x00000000, 0x001C0000}};
  s21_from_int_to_decimal(num1, &a);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST

START_TEST(div_32) {
  int num1 = 11111112;
  // float num2 = 0.000011;
  s21_decimal a = {0};
  s21_decimal b = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0};
  s21_decimal res = {{0x00156633, 0x00000000, 0x00000000, 0x001C0000}};
  s21_from_int_to_decimal(num1, &a);
  // s21_from_float_to_decimal(num2, &b);
  // printf("$$$$$$$$");
  // print_decimal(a);
  // print_decimal(b);
  // printf("$$$$$$$$");
  s21_decimal res_dec = {0};
  s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  // print_decimal(res);
  ck_assert_uint_eq(s21_is_equal(res, res_dec), 1);
}
END_TEST
Suite *suite_div(void) {
  Suite *s = suite_create("div");
  TCase *tc = tcase_create("div");
  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_13);
  tcase_add_test(tc, div_14);
  tcase_add_test(tc, div_15);
  tcase_add_test(tc, div_exp);
  tcase_add_test(tc, div_16);
  tcase_add_test(tc, div_17);
  tcase_add_test(tc, div_18);
  tcase_add_test(tc, div_19);
  tcase_add_test(tc, div_20);
  tcase_add_test(tc, div_21);
  tcase_add_test(tc, div_22);
  tcase_add_test(tc, div_23);
  tcase_add_test(tc, div_24);
  tcase_add_test(tc, div_25);
  tcase_add_test(tc, div_26);
  tcase_add_test(tc, div_27);
  tcase_add_test(tc, div_28);
  tcase_add_test(tc, div_29);
  tcase_add_test(tc, div_30);
  tcase_add_test(tc, div_31);

  suite_add_tcase(s, tc);

  return s;
}
