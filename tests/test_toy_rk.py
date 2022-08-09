from hypernova.hypernova_c.lib import solver_toy_problem_test, free_solver_solution
import pytest


def test_solver_toy_problem_test():
    solution = solver_toy_problem_test()
    assert solution.y[20][0] == pytest.approx(2.0, rel=1e-2)

    free_solver_solution(solution)
    assert True
