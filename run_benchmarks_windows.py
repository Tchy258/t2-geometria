import os
import subprocess
import itertools
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor, as_completed

# Parameters
times = [5]
percentage_on_hull = [0.0001, 0.001, 0.01, 0.10, 0.30, 0.50, 0.70, 1.00]
colinear_amount = [0, 3, 10]
seed = [123]

# Paths
MAIN = Path("./build/release/src/performance_testers").resolve()
CURRENT_DIR = Path.cwd()
MAX_PARALLEL = 5  # Max number of concurrent processes

def run_executable(exe_path, args):
    try:
        print(f"Running: {exe_path} {' '.join(map(str, args))}")
        result = subprocess.run([str(exe_path)] + list(map(str, args)),
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                text=True)
        if result.returncode != 0:
            print(f"Error: {exe_path} failed with return code {result.returncode}")
            print(f"Stderr: {result.stderr.strip()}")
        else:
            print(f"Success: {exe_path} {' '.join(map(str, args))}")
    except Exception as e:
        print(f"Exception running {exe_path}: {e}")

def process_outer_circle():
    dir_path = MAIN / "outer_circle"
    exe_files = list(dir_path.glob("*.exe"))
    tasks = []

    with ThreadPoolExecutor(max_workers=MAX_PARALLEL) as executor:
        for exe in exe_files:
            basename = CURRENT_DIR / exe.stem
            for T, P, C, S in itertools.product(times, percentage_on_hull, colinear_amount, seed):
                N = f"{basename}_{int(P*100) if P * 100 > 1 else P*100}_{C}.csv"
                args = [T, P, C, S, str(N)]
                tasks.append(executor.submit(run_executable, exe, args))

        for future in as_completed(tasks):
            future.result()

def process_simple_dir(subdir):
    dir_path = MAIN / subdir
    exe_files = list(dir_path.glob("*.exe"))
    tasks = []

    with ThreadPoolExecutor(max_workers=MAX_PARALLEL) as executor:
        for exe in exe_files:
            basename = CURRENT_DIR / exe.stem
            for T, S in itertools.product(times, seed):
                N = f"{basename}.csv"
                args = [T, S, str(N)]
                tasks.append(executor.submit(run_executable, exe, args))

        for future in as_completed(tasks):
            future.result()

# Main execution
if __name__ == "__main__":
    process_outer_circle()
    process_simple_dir("random_points")
    # No usar antes de cambiar los tamaños a algo pequeño, por ejemplo 100,
    # ya que verificar si ya 10000 puntos son no colineales toma aproximadamente 8 horas
    #process_simple_dir("random_points/non_colinear")
    process_simple_dir("random_points/at_least_three_colinear")
