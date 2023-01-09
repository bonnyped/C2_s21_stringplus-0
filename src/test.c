#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(strcmp_test) {
  char *str1 = "\0Hello HamleT!";
  char *str2 = "Hello Ham\0leT!";
  char *str3 = "Hello HamleT!";
  char *str4 = "Hello HamleT!";
  char *str5 = "123dom7890";
  char *str6 = "123dom789O";
  char *str7 = "l23dom7890";
  char *str8 = "123dom7890";
  ck_assert_int_eq(strcmp(str1, str2), s21_strcmp(str1, str2));
  ck_assert_int_eq(strcmp(str3, str4), s21_strcmp(str3, str4));
  ck_assert_int_eq(strcmp(str5, str6), s21_strcmp(str5, str6));
  ck_assert_int_eq(strcmp(str7, str8), s21_strcmp(str7, str8));
  ck_assert_int_eq(strcmp("", ""), s21_strcmp("", ""));
}
END_TEST

START_TEST(strncmp_test) {
  char *str1 = "\0Hello HamleT!";
  char *str2 = "\0Hello HamleT!";
  char *str3 = "Hello HamleT!";
  char *str4 = "Hello HamleT!";
  char *str5 = "123dom7890";
  char *str6 = "123dom789O";
  char *str7 = "123dom7890";
  char *str8 = "123dom789O";
  ck_assert_int_eq(strncmp(str1, str2, 100), s21_strncmp(str1, str2, 100));
  ck_assert_int_eq(strncmp(str3, str4, 100), s21_strncmp(str3, str4, 100));
  ck_assert_int_eq(strncmp(str5, str6, 10), s21_strncmp(str5, str6, 10));
  ck_assert_int_eq(strncmp(str7, str8, 1), s21_strncmp(str7, str8, 1));
  ck_assert_int_eq(strncmp("1", "1", 100), s21_strncmp("1", "1", 100));
  ck_assert_int_eq(strncmp("1h", "1g", 10), s21_strncmp("1h", "1g", 10));
}
END_TEST

START_TEST(strcpy_test) {
  char src[100] = "Hello Hamlet";
  char dest[100] = "";
  char src2[100] = "Hello Hamlet";
  char dest2[100] = "";
  ck_assert_str_eq(strcpy(src, dest), s21_strcpy(src, dest));
  ck_assert_str_eq(strcpy(dest2, src2), s21_strcpy(dest2, src2));
}
END_TEST

START_TEST(strncpy_test) {
  char src[100] = "Hello Hamlet";
  char dest[100] = "";
  char src2[100] = "Hello Hamlet";
  char dest2[100] = "\0rop\0";
  ck_assert_str_eq(strncpy(dest, src, 1), s21_strncpy(dest, src, 1));
  ck_assert_str_eq(strncpy(dest2, src2, 1), s21_strncpy(dest2, src2, 1));
}
END_TEST

START_TEST(strcspn_test) {
  char *str1 = "123456788990";
  char *str2 = "t";
  char *str3 = "123456788990";
  char *str4 = "99";
  char *str5 = "";
  char *str6 = "1";
  ck_assert_int_eq(strcspn(str1, str2), s21_strcspn(str1, str2));
  ck_assert_int_eq(strcspn(str3, str4), s21_strcspn(str3, str4));
  ck_assert_int_eq(strcspn(str5, str6), s21_strcspn(str5, str6));
}
END_TEST

START_TEST(strerror_test) {
  for (int i = -300; i < 301; i++) {
    ck_assert_str_eq(strerror(i), s21_strerror(i));
  }
}
END_TEST

START_TEST(strlen_test) {
  char *str = "Hello, this is 21 len";
  char *str1 = "Hello Hamlet";
  char *str2 = "Hello \0Hamlet";
  char *str3 = "123456789";
  char *str4 = "";
  char *str5 = "Hello Hamlet!!!!";
  char *str6 = "1";
  char *str7 = "Hello HamletHello HamletHello HamletHello HamletHello "
               "HamletHello HamletHello HamletHello HamletHello Hamlet";
  // char *str8 = NULL;
  ck_assert_int_eq(strlen(str), s21_strlen(str));
  ck_assert_int_eq(strlen(str1), s21_strlen(str1));
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));
  ck_assert_int_eq(strlen(str4), s21_strlen(str4));
  ck_assert_int_eq(strlen(str5), s21_strlen(str5));
  ck_assert_int_eq(strlen(str6), s21_strlen(str6));
  ck_assert_int_eq(strlen(str7), s21_strlen(str7));
  // ck_assert_int_eq(s21_strlen(str8), s21_strlen(str8));
}
END_TEST

START_TEST(strpbrk_test) {
  char *str1 = "hellohamlet";
  char *str2 = "lov";
  char *str3 = "hellohamlet";
  char *str4 = "t";
  char *str5 = "hellohamlet";
  char *str6 = "h";
  // char *str7 = NULL;
  // char *str8 = NULL;
  ck_assert_str_eq(strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_str_eq(strpbrk(str3, str4), s21_strpbrk(str3, str4));
  ck_assert_str_eq(strpbrk(str5, str6), s21_strpbrk(str5, str6));
  // ck_assert_str_eq(strpbrk(str7, str8), s21_strpbrk(str7, str8));
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, strlen_test);
  tcase_add_test(tc1_1, strcspn_test);
  tcase_add_test(tc1_1, strcmp_test);
  tcase_add_test(tc1_1, strncmp_test);
  tcase_add_test(tc1_1, strcpy_test);
  tcase_add_test(tc1_1, strncpy_test);
  tcase_add_test(tc1_1, strpbrk_test);
  tcase_add_test(tc1_1, strerror_test);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
