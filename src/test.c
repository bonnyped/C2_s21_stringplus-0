#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(sprintf_test_int1) {
  int i1 = 1234;
  char res[200];
  char resorig[200];
  char format[] = "%d % d %+ d % +d %5.1d %+1.6d\n";
  s21_sprintf(res, format, i1, i1, i1, i1, i1, i1);
  sprintf(resorig, format, i1, i1, i1, i1, i1, i1);
  ck_assert_str_eq(res, resorig);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, sprintf_test_int1);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
