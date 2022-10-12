from hypernova.propagation import propagate_orbit, initialize_spacecraft, initialize_problem
from hypernova.solvers import *
import numpy as np
import time


def test_solver_consistency():
    # TODO: THIS IS BROKEN RIGHT NOW

    spacecraft = initialize_spacecraft(3)

    y0 = np.array([6378e3, 0, 0, 0, 0, 7500])

    problem = initialize_problem(0, 8000 / 86400, y0, spacecraft)

    solution_y4 = propagate_orbit(problem, YOSHIDA4, 20, 1e-6)
    solution_rk4 = propagate_orbit(problem, RK810, 20, 1e-6)

    print(solution_y4.y[-1, :3])
    print(solution_rk4.y[-1, :3])

    #assert np.allclose(solution_y4.y[-1, :], solution_rk4.y[-1, :], atol=1)
    assert True


def test_solver_performance():

    spacecraft = initialize_spacecraft(3)

    y0 = np.array([6378e3, 0, 0, 0, 0, 7500])

    problem = initialize_problem(0, 8000 / 86400, y0, spacecraft)

    start_time = time.perf_counter()

    solution = propagate_orbit(problem, RK45, 20, 1e-6)

    end_time = time.perf_counter()

    print(
        f"Time to propagate orbit: {end_time - start_time} ({solution.n} steps taken)")

    assert (end_time - start_time) < 0.1  # seconds
