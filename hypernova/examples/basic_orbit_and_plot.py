from ..solvers.solver_configurations import YOSHIDA4
from hypernova.visualization import plot_orbit
from hypernova.solvers import RK45, YOSHIDA8
from hypernova.propagation import propagate_orbit, initialize_spacecraft, initialize_problem

def basic_orbit_and_plot():
    spacecraft = initialize_spacecraft(3)
    problem = initialize_problem(0, 8000 / 86400, [6878e3, 0, 0, 0, 0, 7600], spacecraft)

    solution = propagate_orbit(problem, YOSHIDA4, 20, 1e-6)

    plot_orbit(solution, title="Yoshida 8th Order", show=True)

if __name__ == "__main__":
    basic_orbit_and_plot()
