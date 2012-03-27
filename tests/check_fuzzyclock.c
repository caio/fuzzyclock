#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../src/fuzzyclock.h"

START_TEST(test_get_hour_string) {
    fail_if(strcmp(get_hour_string(1), "one") != 0, NULL);
    fail_if(strcmp(get_hour_string(2), "two") != 0, NULL);
    fail_if(strcmp(get_hour_string(3), "three") != 0, NULL);
    fail_if(strcmp(get_hour_string(4), "four") != 0, NULL);
    fail_if(strcmp(get_hour_string(5), "five") != 0, NULL);
    fail_if(strcmp(get_hour_string(6), "six") != 0, NULL);
    fail_if(strcmp(get_hour_string(7), "seven") != 0, NULL);
    fail_if(strcmp(get_hour_string(8), "eight") != 0, NULL);
    fail_if(strcmp(get_hour_string(9), "nine") != 0, NULL);
    fail_if(strcmp(get_hour_string(10), "ten") != 0, NULL);
    fail_if(strcmp(get_hour_string(11), "eleven") != 0, NULL);
    fail_if(strcmp(get_hour_string(12), "twelve") != 0, NULL);
}
END_TEST

Suite* fuzzy_suite(void) {
    Suite* suite = suite_create("fuzzyclock");

    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_get_hour_string);
    suite_add_tcase(suite, tc_core);

    return suite;
}

int main(int argc, char const* argv[])
{
    int num_failed = 0;
    Suite* suite = fuzzy_suite();
    SRunner* runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    num_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}


