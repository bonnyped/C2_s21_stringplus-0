#include <check.h>
#include <string.h>
#include <stdlib.h>

#include "s21_string.h"

START_TEST(strlen_test) {
    char* str = "Hello, this is 21 len";

    ck_assert_int_eq(strlen(str), s21_strlen(str));
}
END_TEST

START_TEST(strcat_test) {
    char str[30] = "Hello, this is 21 len";

    ck_assert_str_eq(strcat(str, " test"), s21_strcat(str, " test"));
}
END_TEST

int main() {
    Suite *s = suite_create("String suite");
    TCase *tc = tcase_create("String test case");
    SRunner *runner = srunner_create(s);

    suite_add_tcase(s, tc);
    tcase_add_test(tc, strlen_test);
    tcase_add_test(tc, strcat_test);

    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);

    return 0;
}
