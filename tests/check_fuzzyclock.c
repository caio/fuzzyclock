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

START_TEST(test_zero_should_be_twelve) {
    fail_if(strcmp(get_hour_string(0), "twelve") != 0, NULL);
}
END_TEST

void fuzzy_time_test_gen(int hour, int min, int start, int end,
                         char* expect_mask, int iter_on_hour) {

    char buff[MAX_MSG_SIZE];
    char test[MAX_MSG_SIZE];
    time_t now = time(NULL);
    struct tm* clock = localtime(&now);
    int i = 0;

    clock->tm_min = min;
    clock->tm_hour = hour;

    // The expected hour on the fuzzy output in this
    // case is the next hour
    if (!iter_on_hour && start >= 33) {
        hour++;
    }

    for (i = start; i < end; i++) {
        if (iter_on_hour) { clock->tm_hour = i; }
        else { clock->tm_min = i; }

        snprintf(test, MAX_MSG_SIZE, expect_mask,
                 get_hour_string((iter_on_hour) ? i : hour));

        get_fuzzy_time(clock, buff);

        fail_if(strcmp(test, buff) != 0, "T%0d:WANTED \"%s\", GOT \"%s\"", i, test, buff);
    }
}

START_TEST(test_oclock) {
    int i;
    for (i = 0; i < 3; i++) {
        fuzzy_time_test_gen(1, i, 1, 13, "%s o' clock", 1);
    }
}
END_TEST

START_TEST(test_fivepast) {
    fuzzy_time_test_gen(1, 0, 3, 8, "five past %s", 0);
}
END_TEST

START_TEST(test_tenpast) {
    fuzzy_time_test_gen(1, 0, 8, 13, "ten past %s", 0);
}
END_TEST

START_TEST(test_quarterpast) {
    fuzzy_time_test_gen(1, 0, 13, 18, "quarter past %s", 0);
}
END_TEST

START_TEST(test_twentypast) {
    fuzzy_time_test_gen(1, 0, 18, 23, "twenty past %s", 0);
}
END_TEST

START_TEST(test_twentyfivepast) {
    fuzzy_time_test_gen(1, 0, 23, 28, "twenty five past %s", 0);
}
END_TEST

START_TEST(test_halfpast) {
    fuzzy_time_test_gen(1, 0, 28, 33, "half past %s", 0);
}
END_TEST

START_TEST(test_twentyfiveto) {
    fuzzy_time_test_gen(1, 0, 33, 38, "twenty five to %s", 0);
}
END_TEST

START_TEST(test_twentyto) {
    fuzzy_time_test_gen(1, 0, 38, 43, "twenty to %s", 0);
}
END_TEST

START_TEST(test_quarterto) {
    fuzzy_time_test_gen(1, 0, 43, 48, "quarter to %s", 0);
}
END_TEST

START_TEST(test_tento) {
    fuzzy_time_test_gen(1, 0, 48, 53, "ten to %s", 0);
}
END_TEST

START_TEST(test_fiveto) {
    fuzzy_time_test_gen(1, 0, 53, 58, "five to %s", 0);
}
END_TEST

Suite* fuzzy_suite(void) {
    Suite* suite = suite_create("fuzzyclock");

    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_get_hour_string);
    tcase_add_test(tc_core, test_oclock);

    tcase_add_test(tc_core, test_fivepast);
    tcase_add_test(tc_core, test_tenpast);
    tcase_add_test(tc_core, test_quarterpast);
    tcase_add_test(tc_core, test_twentypast);
    tcase_add_test(tc_core, test_twentyfivepast);
    tcase_add_test(tc_core, test_halfpast);

    tcase_add_test(tc_core, test_twentyfiveto);
    tcase_add_test(tc_core, test_twentyto);
    tcase_add_test(tc_core, test_quarterto);
    tcase_add_test(tc_core, test_tento);
    tcase_add_test(tc_core, test_fiveto);

    // corner cases
    tcase_add_test(tc_core, test_zero_should_be_twelve);

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


