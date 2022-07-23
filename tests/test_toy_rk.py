from supernova.supernova_c.lib import solver_toy_problem_test
from supernova.supernova_c import ffi
import pytest


def test_solver_toy_problem_test():
    solver_toy_problem_test()
    # TODO: Make test proper, fix memory leak during gc
    assert True
