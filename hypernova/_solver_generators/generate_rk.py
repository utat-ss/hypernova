# Generates the C source code for a Runge Kutta solver.

class ButcherTableau:
    def __init__(self, A, B, C):
        self.A = A
        self.B = B
        self.C = C
        self.num_stages = len(C)


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
