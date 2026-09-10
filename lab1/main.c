#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef FLOAT_DOUBLE_TEST
typedef double energy_t;
typedef double count_t;
typedef double percentage_t;
typedef double distance_t;
typedef double duration_t;
typedef double currency_t;

static const char* const ENERGY_FORMAT = "%lf";
static const char* const CURRENCY_FORMAT = "%lf";
static const char* const COUNT_FORMAT = "%lf";
static const char* const PERCENTAGE_FORMAT = "%lf";
static const char* const DISTANCE_FORMAT = "%lf";
static const char* const DURATION_FORMAT = "%lf";
#endif

#define scan_or_fail(fmt, var) do { if (scanf((fmt), &(var)) != 1) { fprintf(stderr, "Error reading into variable: %s\n", #var); exit(-1); }} while (0)

struct trip_statistics_s {
    duration_t duration_hrs;
    distance_t average_speed_kmh;

    energy_t   energy_used_kWh;
    energy_t   consumption_per_100km;

    currency_t trip_cost;
    currency_t trip_cost_per_person;
}; typedef struct trip_statistics_s trip_statistics_t;

trip_statistics_t trip_statistics_calculate(distance_t distance_km, duration_t duration_min, 
    percentage_t bat_level_start, percentage_t bat_level_finish, energy_t bat_capacity,
    currency_t energy_tariff_byn, count_t passengers_count) {
    
    const duration_t duration_hours = duration_min / 60.0;
    const energy_t   energy_used_kWh = (bat_capacity * (bat_level_start - bat_level_finish)) / 100.0;
    const distance_t average_speed  = distance_km / duration_hours;
    const energy_t   consumption_per_100km = energy_used_kWh / distance_km * 100.0;
    const currency_t trip_cost = energy_used_kWh * energy_tariff_byn;
    const currency_t trip_cost_per_passenger = trip_cost / passengers_count;

    return (trip_statistics_t) {
        .duration_hrs = duration_hours,
        .energy_used_kWh = energy_used_kWh,
        .average_speed_kmh = average_speed,
        .consumption_per_100km = consumption_per_100km,
        .trip_cost = trip_cost,
        .trip_cost_per_person = trip_cost_per_passenger,
    };

}

int main(int argc, char** argv) {
    unsigned int run_self_test = 0;
    if (argc > 1 && !strcmp(argv[1], "--self-test")) { run_self_test = 1; }

    distance_t   distance_km;
    duration_t   duration_min;
    percentage_t bat_level_start;
    percentage_t bat_level_finish;
    energy_t     bat_capacity;
    currency_t   energy_tariff_byn;
    count_t      passengers_count;


    scan_or_fail(DISTANCE_FORMAT, distance_km);
    scan_or_fail(DURATION_FORMAT, duration_min);
    scan_or_fail(ENERGY_FORMAT, bat_capacity);
    scan_or_fail(PERCENTAGE_FORMAT, bat_level_start);
    scan_or_fail(PERCENTAGE_FORMAT, bat_level_finish);
    scan_or_fail(CURRENCY_FORMAT, energy_tariff_byn);
    scan_or_fail(COUNT_FORMAT, passengers_count);

    trip_statistics_t trip_stats = trip_statistics_calculate(distance_km, duration_min, bat_level_start, bat_level_finish, bat_capacity, energy_tariff_byn, passengers_count);

    printf(DURATION_FORMAT, trip_stats.duration_hrs); printf("%s", ",");
    printf(ENERGY_FORMAT, trip_stats.energy_used_kWh); printf("%s", ",");
    printf(DISTANCE_FORMAT, trip_stats.average_speed_kmh); printf("%s", ",");
    printf(ENERGY_FORMAT, trip_stats.consumption_per_100km); printf("%s", ",");
    printf(CURRENCY_FORMAT, trip_stats.trip_cost); printf("%s", ",");
    printf(CURRENCY_FORMAT, trip_stats.trip_cost_per_person); printf("%s", "\n");

    if (run_self_test) {
        int tests_failed = 0;
        #define assert_eq(v1, v2) if ((v1) != (v2)) { fprintf(stderr, "Assertion error (E = %5.2f%%): (%-55s) != (%30s) [%-30.20lf != %30.20lf]\n",(__max((v1),(v2))-__min((v1),(v2)))/(__max((v1),(v2))), #v1, #v2, (v1), (v2)); tests_failed += 1; }

        assert_eq(trip_stats.average_speed_kmh * trip_stats.duration_hrs, distance_km);
        assert_eq(trip_stats.consumption_per_100km * distance_km / 100.0, trip_stats.energy_used_kWh);
        assert_eq(trip_stats.trip_cost_per_person * passengers_count, trip_stats.trip_cost);

        if (tests_failed) {
            return -1;
        }
    }
    

    return 0;
}