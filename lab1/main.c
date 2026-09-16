/// clang-specific warning of using scanf() function
//  ignored, because constraints of task only allow using scanf() and printf()
#define _CRT_SECURE_NO_WARNIGS

#include <stdio.h>

#if defined(FLOAT_BASE_TYPE)
typedef float real_t;
typedef unsigned integer_t;
#define SCAN_FORMAT "%f %f %f %f %f %f %u"
#else
#include <stdint.h>
typedef double real_t;
typedef uint64_t integer_t;
#define SCAN_FORMAT "%lf %lf %lf %lf %lf %lf %llu"
#endif // FLOAT_BASE_TYPE

#define stringify(x) (#x)

int main() {
  real_t distance_km;
  real_t duration_minutes;
  real_t battery_capacity_kwh;
  real_t start_charge_percent;
  real_t finish_charge_percent;
  real_t tariff_byn_per_kwh;
  integer_t passengers;

  scanf_s(SCAN_FORMAT, &distance_km, &duration_minutes, &battery_capacity_kwh,
          &start_charge_percent, &finish_charge_percent, &tariff_byn_per_kwh,
          &passengers);

  const real_t time_hours                   = duration_minutes / 60.0;
  const real_t energy_used_kwh              = battery_capacity_kwh * (start_charge_percent - finish_charge_percent) / 100.0;
  const real_t average_speed_kmh            = distance_km / time_hours;
  const real_t consumption_kwh_per_100km    = energy_used_kwh / distance_km * 100.0;
  const real_t trip_cost_byn                = energy_used_kwh * tariff_byn_per_kwh;
  const real_t cost_per_passenger_byn       = trip_cost_byn / (integer_t)passengers;

  printf("%-30s %10.4lf (%s)\n", "Energy used: ", (double)energy_used_kwh, "kWh");
  printf("%-30s %10.4lf (%s)\n", "Trip time:", (double)time_hours, "h");
  printf("%-30s %10.4lf (%s)\n", "Average speed:", (double)average_speed_kmh, "km/h");
  printf("%-30s %10.4lf (%s)\n", "Consumption Rate: ", (double)consumption_kwh_per_100km, "kWh/100km");
  printf("%-30s %10.4lf (%s)\n", "Trip cost: ", (double)trip_cost_byn, "BYN");
  printf("%-30s %10.4lf (%s)\n", "Per-passenger cost: ", (double)cost_per_passenger_byn, "BYN/person");
  return 0;
}