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
    "%s o' clock\n",
    "five past %s\n",
    "ten past %s\n",
    "quarter past %s\n",
    "twenty past %s\n",
    "twenty five past %s\n",
    "half past %s\n",
    "twenty five to %s\n",
    "twenty to %s\n",
    "quarter to %s\n",
    "ten to %s\n",
    "five to %s\n",
};

char* const get_hour_string(int hour) {
    return HOUR_NAMES[(hour - 1) % 12];
}

void get_fuzzy_time(struct tm* clock, char* buffer) {
    int index = 0;
    int hour = clock->tm_hour;
    int min = clock->tm_min;

    if (min > 2) {
        index = ((min - 3) / 5) - 1;
    }

    if (index > 6) { hour++; }

    char* timestr = FUZZY_MSG[index];
    char* hourname = get_hour_string(hour);

    snprintf(buffer, MAX_MSG_SIZE, timestr, hourname);
}
