#include "s21_tests.h"

int main(void) {
  int failed = 0;
  Suite *s;
  SRunner *runner;
  s = suite_mul();
  runner = srunner_create(s);

  srunner_add_suite(runner, suite_compare());
  srunner_add_suite(runner, suite_convert());
  srunner_add_suite(runner, suite_add());
  srunner_add_suite(runner, suite_sub());
  srunner_add_suite(runner, suite_div());
  srunner_add_suite(runner, suite_mod());
  srunner_add_suite(runner, suite_floor());
  srunner_add_suite(runner, suite_round());
  srunner_add_suite(runner, suite_truncate());
  srunner_add_suite(runner, suite_negate());

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}