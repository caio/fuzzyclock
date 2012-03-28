#include <stdio.h>
#include <stdlib.h>
#include "fuzzyclock.h"

char* HOUR_NAMES[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "ten",
    "eleven",
    "twelve",
};

char* FUZZY_MSG[] = {
    "%s o' clock",
    "five past %s",
    "ten past %s",
    "quarter past %s",
    "twenty past %s",
    "twenty five past %s",
    "half past %s",
    "twenty five to %s",
    "twenty to %s",
    "quarter to %s",
    "ten to %s",
    "five to %s",
};

char* const get_hour_string(int hour) {
    return HOUR_NAMES[(hour - 1) % 12];
}

void get_fuzzy_time(struct tm* clock, char* buffer) {
    int index = 0;
    int hour = clock->tm_hour;
    int min = clock->tm_min;

    if (min > 2) {
        index = ((min - 3) / 5) + 1;
    }

    if (index > 6) { hour++; }

    char* timestr = FUZZY_MSG[index];
    char* hourname = get_hour_string(hour);

    snprintf(buffer, MAX_MSG_SIZE, timestr, hourname);
}
