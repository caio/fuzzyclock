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

START_TEST(test_oclock) {
    char buff[MAX_MSG_SIZE];
    char test[MAX_MSG_SIZE];
    time_t now = time(NULL);
    struct tm* clock = localtime(&now);
    int i = 0;

    // Verifying o' clock
    clock->tm_min = 0;

    for (i = 1; i < 12; i++) {
        clock->tm_hour = i;
        snprintf(test, MAX_MSG_SIZE, "%s o' clock", get_hour_string(i));

        get_fuzzy_time(clock, buff);

        fail_if(strcmp(test, buff) != 0, "WANTED \"%s\", GOT \"%s\"", test, buff);
    }
}
END_TEST

START_TEST(test_fivepast) {
    char buff[MAX_MSG_SIZE];
    char test[MAX_MSG_SIZE];
    time_t now = time(NULL);
    struct tm* clock = localtime(&now);
    int i = 0;

    // Verifying "five past"

    clock->tm_hour = 1;

    for (i = 3; i < 8; i++) {
        clock->tm_min = i;

        snprintf(test, MAX_MSG_SIZE, "five past one");

        get_fuzzy_time(clock, buff);

        fail_if(strcmp(test, buff) != 0, "WANTED \"%s\", GOT \"%s\"", test, buff);
    }
}
END_TEST

Suite* fuzzy_suite(void) {
    Suite* suite = suite_create("fuzzyclock");

    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_get_hour_string);
    tcase_add_test(tc_core, test_oclock);
    /* tcase_add_test(tc_core, test_fivepast); */

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


