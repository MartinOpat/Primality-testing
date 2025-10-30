import os
import time
import pickle
import numpy as np

n = int(input("Alg to run: "))

with open("data/primes50.txt") as f:
    nums = [int(x) for x in f.read().strip("\n").split()]
    # print(nums[0])

    times = [[-1, -1]] * len(nums)

    test_nums = [nums[i] for i in range(0, len(nums), 1000)]
    reps = 10
    for i, x in enumerate(test_nums):
        meas = []
        for j in range(reps):
            start = time.time()
            os.system(f"./build/PrimalityTesting {n} {x}")
            end = time.time()
            meas.append(end - start)
        times[i] = [np.mean(meas), np.std(meas) / np.sqrt(len(meas))]

    print(times[:3])
    s = f"data/large_times_{n}.txt"
    if os.path.isfile(s):
        os.system(f"rm {s}")
    with open(s, "wb") as g:
        pickle.dump(times, g)
