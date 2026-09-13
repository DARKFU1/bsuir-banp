import time
import numpy as np
import pandas as pd
import io
import subprocess
import random


def round_to_hundredths(f: float):
    return float("{:.2f}".format(f))

def compare_floats_with_eps(a, b):
    if a < b:
        a, b = b, a

    if round_to_hundredths(a) == round_to_hundredths(b) or (round_to_hundredths(a) < round_to_hundredths(b) and round_to_hundredths(a + np.finfo(np.float64).eps) > round_to_hundredths(b)):
        return True

    return False

def run_static_tests():
    INPUT_FILE_NAME = "input.csv"

    input_csv = pd.read_csv(INPUT_FILE_NAME)
    df = pd.DataFrame(input_csv)
    rows = df.iterrows()

    output_csv = open("output.csv", "w")
    output_csv.write("duration_hr,energy_used,average_speed,consumption_rate,trip_cost,trip_cost_per_person\n")

    expected_csv = pd.read_csv("expected.csv")

    for i, row in rows:
        str_csv = "{} {} {} {} {} {} {}".format(row["distance"], row["time"], row["capacity"], row["start"], row["finish"], row["tariff"], row["people"])

        # print(row)

        print("[ {:2}/{:2} ] Running {} {}".format(i, len(df.index), "a.exe", str_csv), end="\r")
        prog = subprocess.Popen(["a.exe"], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
        data = prog.communicate(str_csv.encode())[0].decode()
        
        expected_data = expected_csv.iloc[0]
        data = data.strip().split(',')

        print("\ndata: {}\nexpected: {}\n".format(data, expected_data))

def run_dynamic_tests():
    random.seed(time.time_ns())

    INPUT_FILE_NAME = "input.csv"

    output_csv = open("output.dynamic.csv", "w")
    output_csv.write("time_coefficient,capacity_coefficient,distance_coefficient,tariff_coefficient,people_coefficient,duration_hr,energy_used,average_speed,consumption_rate,trip_cost,trip_cost_per_person\n")

    input_csv = pd.read_csv(INPUT_FILE_NAME)
    df = pd.DataFrame(input_csv)
    rows = df.iterrows()

    duration_tests_failed = 0

    test_no = 0
    for i, row in rows:
        print("Running [ {:02}/{:02} ]".format(test_no, len(df)), end = "\r")
        str_csv = "{} {} {} {} {} {} {}".format(
                row["distance"], row["time"], row["capacity"], 
                row["start"], row["finish"], row["tariff"], row["people"]
        )

        prog = subprocess.Popen(["a.exe"], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
        original_data = prog.communicate(str_csv.encode())[0].decode()
        original_data = original_data.strip().split(',')

        original_duration_hr           = float(original_data[0])
        original_energy_used           = float(original_data[1])
        original_average_speed         = float(original_data[2])
        original_consumption_rate      = float(original_data[3])
        original_trip_cost             = float(original_data[3])
        original_trip_cost_per_person  = float(original_data[3])

        distance_coefficient = 4000 * random.randint(1, 1024) 
        time_coefficient     = 4000 * random.randint(1, 1024) / 256
        capacity_coefficient = 4000 * random.randint(1, 1024) / 256
        price_coefficient    = 4000 * random.randint(1, 1024) / 256
        people_coefficient   = 4000 * random.randint(1, 10)

        str_csv = "{} {} {} {} {} {} {}".format(
                distance_coefficient * row["distance"], time_coefficient * row["time"], capacity_coefficient * row["capacity"], 
                row["start"], row["finish"], price_coefficient * row["tariff"], people_coefficient * row["people"]
        )

        prog_new = subprocess.Popen(["a.exe", "--self-test", "--no-rounding"], stdout=subprocess.PIPE, stdin=subprocess.PIPE)

        new_data = prog_new.communicate(str_csv.encode())[0].decode().strip().split(',')


        new_duration_hr          = float(new_data[0])
        new_energy_used          = float(new_data[1])
        new_average_speed        = float(new_data[2])
        new_consumption_rate     = float(new_data[3])
        new_trip_cost            = float(new_data[4])
        new_trip_cost_per_person = float(new_data[5])


        if round_to_hundredths(new_duration_hr) != round_to_hundredths(round_to_hundredths(original_duration_hr) * (time_coefficient)):
            duration_tests_failed += 1
            print("{:.2f} != {:.2f} * {:.2f}".format(new_duration_hr, original_duration_hr, time_coefficient))
            print("1")

        if round_to_hundredths(new_energy_used) != round_to_hundredths(original_energy_used * distance_coefficient * time_coefficient):
            print("{:.2f} != {:.2f} * {:.2f} * {:.2f}".format(new_energy_used, original_energy_used, distance_coefficient, time_coefficient))
            print("2")

        if round_to_hundredths(new_average_speed * time_coefficient) != round_to_hundredths(original_average_speed * distance_coefficient):
            print("{:.2f} != {:.2f} * {:.2f}".format(new_average_speed, original_average_speed, time_coefficient))
            print("3")

        if round_to_hundredths(new_consumption_rate * distance_coefficient) != round_to_hundredths(original_duration_hr * capacity_coefficient):
            print("{:.2f} * {:.2f} != {:.2f} * {:.2f}".format(new_consumption_rate, distance_coefficient, original_duration_hr, capacity_coefficient))
            print("4")

        if new_trip_cost != round_to_hundredths(original_trip_cost * distance_coefficient * price_coefficient):
            print("{:.2f} != {:.2f} * {:.2f}".format(new_trip_cost, original_trip_cost, time_coefficient))
            print("5")

        if new_trip_cost_per_person != round_to_hundredths(original_trip_cost_per_person * distance_coefficient * price_coefficient * people_coefficient):
            print("6")

        test_no+=1

        print(original_data, new_data)
    
    print("Duration tests failed: {}".format(duration_tests_failed))


    

run_dynamic_tests()
# print("[ {:2}/{:2} ] Done! {}".format(len(df.index), len(df.index), " " * 200), end="\r")
