# Generates the C source code for a Runge Kutta solver.
import numpy as np


class ButcherTableau:
    def __init__(self, A: np.ndarray, B: np.ndarray, C: np.ndarray, solver_name: str):
        self.A = A
        self.B = B
        self.C = C
        self.num_stages = len(C)
        self.solver_name = solver_name

    def to_c_literal(self):
        # pretty print to C literal

        pretty_print_A = '{'
        for i in range(self.num_stages):
            pretty_print_A += '{'
            for j in range(self.num_stages):
                pretty_print_A += '{:.16f}'.format(self.A[i][j])
                if j < self.num_stages - 1:
                    pretty_print_A += ', '
            pretty_print_A += '}'
            if i < self.num_stages - 1:
                pretty_print_A += ', '
        pretty_print_A += '}'

        pretty_print_B = '{' + ', '.join(['{:.16f}'.format(self.B[i])
                                         for i in range(self.num_stages)]) + '}'
        pretty_print_C = '{' + ', '.join(['{:.16f}'.format(self.C[i])
                                         for i in range(self.num_stages)]) + '}'

        return f"const double {self.solver_name}_A[{self.num_stages}][{self.num_stages}] = {pretty_print_A};\n" \
               f"const double {self.solver_name}_B[{self.num_stages}] = {pretty_print_B};\n"\
               f"const double {self.solver_name}_C[{self.num_stages}] = {pretty_print_C};\n"


def generate_rk(solver_order: int, butcher_tableau: ButcherTableau, adaptive: bool, error_correlation: str = None):
    '''
    Generate the C source code for a Runge Kutta solver.

    Parameters
    ----------
    solver_order : int
        The order of the solver.
    butcher_tableau : ButcherTableau
        The Butcher tableau for the solver.
    adaptive : bool
        Whether the solver is adaptive.
    error_correlation : str
        The error correlation to use, implemented as direct C source code.
    '''
