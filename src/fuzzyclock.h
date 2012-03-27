#ifndef __FUZZYCLOCK_H__

#define __FUZZYCLOCK_H__

#include <time.h>

#define MAX_MSG_SIZE 30

void get_fuzzy_time(struct tm*, char*);

char* const get_hour_string(int hour);

#endif
