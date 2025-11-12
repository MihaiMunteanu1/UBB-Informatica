from subprocess import run as prun
import time as stime

configs_v1 = [
    {"p":[5], "t":"1"},
    {"p":[5,9,17], "t":"2"},
    {"p":[5,9,17], "t":"3"},
]

configs_v2 = [
    {"p":[4], "t":"1"},
    {"p":[4,8,16], "t":"2"},
    {"p":[4,8,16], "t":"3"},
]
configs_v3 = [
    {"p":[5], "t":"1"},
    {"p":[5,9,17], "t":"2"},
    {"p":[5,9,17], "t":"3"},
]

configs_secv =[
    {"v":"1", "t":"1"},
    {"v":"1", "t":"2"},
    {"v":"1", "t":"3"},

    {"v":"2", "t":"1"},
    {"v":"2", "t":"2"},
    {"v":"2", "t":"3"},

    {"v":"3", "t":"1"},
    {"v":"3", "t":"2"},
    {"v":"3", "t":"3"},
]


def run_config(varianta):
    results = []
    if varianta=="1":
        configs = configs_v1
    elif varianta=="2":
        configs = configs_v2
    else:
        configs = configs_v3

    for c in configs:
        test = c.get("t")
        process_results = []

        for p in c.get("p"):
            times = []
            for i in range(10):
                cmd = f"mpiexec -n {p} -oversubscribe v{varianta}.{varianta} {test}"
                data = prun(cmd, capture_output=True, shell=True, text=True)
                if data.stderr:
                    print(data.stderr)
                    exit(-1)
                try:
                    time_lines = [x for x in data.stdout.splitlines() if "Timp total MPI Varianta" in x]
                    if not time_lines:
                        print(f"No 'Timp total MPI Varianta' lines found in output")
                        exit(-1)
                    time_ms = float(time_lines[-1].split()[-2])
                except Exception as e:
                    print(f"Failed to parse time for test `{test}` with {p} processes, run {i+1}: {e}")
                    exit(-1)
                times.append(time_ms)
                #print(f"Test {test} with {p} processes run {i+1}: {time_ms:.2f}ms")

                result_path = f"Vers{varianta}/data{test}/Numar3.txt"
                result_secv_path = f"Vers{varianta}/data{test}/Numar3Secv.txt"
                try:
                    with open(result_path, 'r') as f1, open(result_secv_path, 'r') as f2:
                        if f1.read() != f2.read():
                            print(f"WARNING: Files differ for test {test}, variant {varianta}, {p} processes")
                except FileNotFoundError:
                    print(f"WARNING: Could not find output files for test {test}, variant {varianta}")

                stime.sleep(1)

            average_for_p = sum(times) / len(times)
            print(f"Varianta {varianta}, Test {test}, {p} processes average: {average_for_p:.2f}ms")
            process_results.append({"processes": p, "times": times, "average": average_for_p})

        all_times = [time for pr in process_results for time in pr["times"]]
        overall_average = sum(all_times) / len(all_times)
        print(f"Varianta {varianta}, Test {test} overall average: {overall_average:.2f}ms")

        results.append({"test": test, "process_results": process_results, "overall_average": overall_average})
    return results


def run_config_secv():
    results = []
    for c in configs_secv:
        test = c.get("t")
        varianta = c.get("v")
        times = []
        for i in range(10):
            cmd = f"mpiexec -n 4 -oversubscribe secv {varianta} {test}"
            data = prun(cmd, capture_output=True, shell=True, text=True)
            if data.stderr:
                print(f"STDERR: {data.stderr}")

            try:
                time_lines = [x for x in data.stdout.splitlines() if x.startswith("Timp total:")]
                if not time_lines:
                    print(f"No 'Timp total:' lines found in output")
                    exit(-1)
                time_ms = float(time_lines[-1].split()[2])
            except Exception as e:
                print(f"Failed to parse time for test `{test}`, run {i+1}: {e}")
                exit(-1)
            times.append(time_ms)
            #print(f"Varianta: {varianta} Test {test} run {i+1}: {time_ms:.2f}ms")
            stime.sleep(1)
        average = sum(times) / len(times)
        print(f"Test {test}, varianta {varianta} average: {average:.2f}ms")
        results.append({"test": test, "times": times, "average": average})
    return results


def run():
     run_config_secv()
     for varianta in ["1","2","3"]:
          run_config(varianta)

run()