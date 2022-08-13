from hypernova.hypernova_c.lib import (initialize_problem, initialize_spacecraft,
                                       propagate_orbit, free_solver_solution)
from hypernova.hypernova_c import ffi
from matplotlib import pyplot as plt
import numpy as np
import time


def test_orbit_propagation():

    spacecraft = initialize_spacecraft(3)

    y0 = [6378e3, 0, 0, 0, 7500, 0]

    problem = initialize_problem(0, 10000 / 86400, y0, spacecraft)

    start_time = time.perf_counter()
    solution = propagate_orbit(problem, 1)

    end_time = time.perf_counter()

    # Ingest data into numpy array
    print(f"Time to propagate orbit: {end_time - start_time} ({solution.n} steps taken)")

    # Read buffer into numpy array
    t = np.frombuffer(ffi.buffer(solution.t, solution.n *
                      ffi.sizeof("double")), dtype=np.double)
    t.shape = (solution.n, 1)

    jd = np.frombuffer(ffi.buffer(solution.jd, solution.n *
                       ffi.sizeof("double")), dtype=np.double)
    jd.shape = (solution.n, 1)

    y = np.frombuffer(ffi.buffer(solution.y, solution.n *
                      6 * ffi.sizeof("double")), dtype=np.double)
    y.shape = (solution.n, 6)

    plt.figure(figsize=(12, 5))
    plt.subplot(131)
    plt.plot(y[:, 0], y[:, 1])
    plt.subplot(132)
    plt.plot(y[:, 0], y[:, 2])
    plt.subplot(133)
    plt.plot(y[:, 1], y[:, 2])
    plt.tight_layout()

    plt.show()

    free_solver_solution(solution)

    assert True
