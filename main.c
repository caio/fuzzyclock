#include <stdio.h>
#include "fuzzyclock.h"


int main(int argc, char const* argv[])
{
    char msg[MAX_MSG_SIZE];
    get_fuzzy_time(time(NULL), msg);
    printf(msg);
    return 0;
}
