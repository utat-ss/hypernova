from hypernova.visualization import plot_orbit
from hypernova.solvers import *
from hypernova.propagation import propagate_orbit, initialize_spacecraft, initialize_problem


def basic_orbit_and_plot():
    spacecraft = initialize_spacecraft(1)
    problem = initialize_problem(
        0, 20, [6878e3, 0, 0, 0, 1000, 7500], spacecraft)

    solver = RK1012

    solution = propagate_orbit(problem, solver, 5, 1e-6)

    print(solution.y.shape)

    plot_orbit(solution, title="RK1012", show=True)


if __name__ == "__main__":
    basic_orbit_and_plot()
