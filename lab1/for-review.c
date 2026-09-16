#include <stdio.h>
#include <stdint.h>

int main(void) {
    double distance_km;
    double duration_minutes;
    double battery_capacity_kwh;
	double start_charge_percent;
	double finish_charge_percent;
	double tariff_byn_per_kwh;
	static uint64_t passengers;

    scanf("%lf %lf %lf %lf %lf %lf %lf",
    &distance_km, &duration_minutes, &battery_capacity_kwh, 
    &start_charge_percent, &finish_charge_percent, &tariff_byn_per_kwh,
    &passengers);

    double time_hours = duration_minutes / 60;
    double energy_used_kwh = battery_capacity_kwh * start_charge_percent - finish_charge_percent / 100.0;
    double average_speed_kmh = distance_km / time_hours;
    double consumption_kwh_per_100km = energy_used_kwh / distance_km * 100;
    double trip_cost_byn = energy_used_kwh * tariff_byn_per_kwh;
    double cost_per_passenger_byn = trip_cost_byn / passengers;

    printf("%-30s %10.4lf (%s)\n", "Energy used: ",         (double)energy_used_kwh,           "kWh");
    printf("%-30s %10.4lf (%s)\n", "Trip time:",            (double)time_hours,                "h");
    printf("%-30s %10.4lf (%s)\n", "Average speed:",        (double)average_speed_kmh,         "km/h");
    printf("%-30s %10.4lf (%s)\n", "Consumption Rate: ",    (double)consumption_kwh_per_100km, "kWh/100km");
    printf("%-30s %10.4lf (%s)\n", "Trip cost: ",           (double)trip_cost_byn,             "BYN");
    printf("%-30s %10.4lf (%s)\n", "Per-passenger cost: ",  (double)cost_per_passenger_byn,    "BYN/person");
    return 0;
}