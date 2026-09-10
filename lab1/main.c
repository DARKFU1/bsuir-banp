#include <stdio.h>

#ifndef FLOAT_DOUBLE_TEST
typedef double energy_t;
typedef double count_t;
typedef double distance_t;
typedef double duration_t;
typedef double currency_t;

static const char* const ENERGY_FORMAT = "%.lf %.lf";
static const char* const CURRECCY_FORMAT = "%.lf %.lf";
static const char* const COUNT_FORMAT = "%.lf %.lf";
static const char* const DISTANCE_FORMAT = "%.lf %.lf";
static const char* const DURATION_FORMAT = "%.lf %.lf";
#endif

int main() {


    printf("%s", "Hello, world!");
    return 0;
}