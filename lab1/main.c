#include <stdio.h>
#include <stdlib.h>

#ifndef FLOAT_DOUBLE_TEST
typedef double energy_t;
typedef double count_t;
typedef double percentage_t;
typedef double distance_t;
typedef double duration_t;
typedef double currency_t;

static const char* const ENERGY_FORMAT = "%.lf";
static const char* const CURRENCY_FORMAT = "%.lf";
static const char* const COUNT_FORMAT = "%.lf";
static const char* const PERCENTAGE_FORMAT = "%.lf";
static const char* const DISTANCE_FORMAT = "%.lf";
static const char* const DURATION_FORMAT = "%.lf";
#endif

#define scan_or_fail(fmt, var) do { if (scanf((fmt), &(var)) != 1) { fprintf(stderr, "Error reading into variable: %s\n", #var); exit(-1); }} while (0)

struct trip_statistics_s {
    duration_t duration_hrs;
    distance_t average_speed_kmh;

    energy_t   energy_used_kWh;
    energy_t   consumption_per_100km;

    currency_t trip_cost;
    currency_t trip_cost_per_person;
};

int main() {
    distance_t   distance_km;
    duration_t   duration_min;
    percentage_t bat_level_start;
    percentage_t bat_level_finish;
    energy_t     bat_capacity;
    currency_t   energy_tariff_byn;
    count_t      passengers_count;


    scan_or_fail(DISTANCE_FORMAT, distance_km);
    scan_or_fail(DURATION_FORMAT, duration_min);
    scan_or_fail(COUNT_FORMAT, passengers_count);
    scan_or_fail(ENERGY_FORMAT, bat_capacity);
    scan_or_fail(PERCENTAGE_FORMAT, bat_level_start);
    scan_or_fail(PERCENTAGE_FORMAT, bat_level_finish);
    scan_or_fail(CURRENCY_FORMAT, energy_tariff_byn);

    printf("%s", "Hello, world!");
    return 0;
}