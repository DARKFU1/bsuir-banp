#include <stdio.h>

int main() {
    double distance_km;
    double duration_minutes;
    double battery_capacity_kwh;
	double start_charge_percent;
	double finish_charge_percent;
	double tariff_byn_per_kwh;
	long passengers;

    scanf_s("%lf %lf %lf %lf %lf %lf %llu",
    &distance_km, &duration_minutes, &battery_capacity_kwh, 
    &start_charge_percent, &finish_charge_percent, &tariff_byn_per_kwh,
    &passengers);

    const double time_hours = duration_minutes / 60.0;
    const double energy_used_kwh = battery_capacity_kwh * (start_charge_percent - finish_charge_percent) / 100.0;
    const double average_speed_kmh = distance_km / time_hours;
    const double consumption_kwh_per_100km = energy_used_kwh / distance_km * 100.0;
    const double trip_cost_byn = energy_used_kwh * tariff_byn_per_kwh;
    const double cost_per_passenger_byn = trip_cost_byn / (long)passengers;

    const float time_hours_float = duration_minutes / 60.0;
    const float energy_used_kwh_float = battery_capacity_kwh * (start_charge_percent - finish_charge_percent) / 100.0;
    const float average_speed_kmh_float = distance_km / time_hours;
    const float consumption_kwh_per_100km_float = energy_used_kwh / distance_km * 100.0;
    const float trip_cost_byn_float = energy_used_kwh * tariff_byn_per_kwh;
    const float cost_per_passenger_byn_float = trip_cost_byn / (long)passengers;


    const char* line_w17 = "-----------------";

    printf("| %6s | %15s | %15s | %15s | %15s | %15s | %15s |\n",
        "Type", "energy_used", "trip_time", "avg_speed", "cons_rate", "trip_cost", "cost_per_pass");
    printf("|%s+%s+%s+%s+%s+%s+%s|\n",
    "--------", line_w17, line_w17, line_w17, line_w17, line_w17, line_w17);
    printf("| %6s | %15.10f | %15.10f | %15.10f | %15.10f | %15.10f | %15.10f |\n",
    "double", energy_used_kwh, time_hours, average_speed_kmh, consumption_kwh_per_100km, trip_cost_byn, cost_per_passenger_byn);
    printf("| %6s | %15.10f | %15.10f | %15.10f | %15.10f | %15.10f | %15.10f |\n",
    "float", energy_used_kwh_float, time_hours_float, average_speed_kmh_float, consumption_kwh_per_100km_float, trip_cost_byn_float, cost_per_passenger_byn_float);
    return 0;
}