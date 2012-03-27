#include <stdio.h>
#include "fuzzyclock.h"


int main(int argc, char const* argv[])
{
    char msg[MAX_MSG_SIZE];
    time_t now = time(NULL);
    get_fuzzy_time(localtime(&now), msg);
    printf(msg);
    return 0;
}
