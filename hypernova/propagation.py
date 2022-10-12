from hypernova.hypernova_c.lib import propagate_orbit as propagate_orbit_c
from hypernova.hypernova_c.lib import initialize_problem as initialize_problem_c
from hypernova.hypernova_c.lib import initialize_spacecraft as initialize_spacecraft_c
from hypernova.hypernova_c.lib import RK, SYMPLECTIC, cast_to_solver
from hypernova.hypernova_c import ffi
from hypernova.solvers import *
from logging import getLogger
from time import perf_counter

import numpy as np


def initialize_spacecraft(mass: float):
    '''
    Initialize a spacecraft structure.

    Parameters
    ----------
    mass : float
        Mass of the spacecraft in kilograms.
    '''
    return initialize_spacecraft_c(mass)


def initialize_problem(t0: float, t1: float, y0: np.ndarray, spacecraft):
    '''
    Initialize a problem structure.

    Parameters
    ----------
    t0 : float
        Initial time in seconds.
    t1 : float
        Final time in seconds.
    y0 : numpy.ndarray
        Initial state vector (x, y, z, vx, vy, vz) in meters and meters/second.
    spacecraft : Spacecraft
        Spacecraft structure.
    '''
    return initialize_problem_c(t0, t1, list(y0), spacecraft)


def propagate_orbit(problem, solver, timestep: float, tol: float) -> SolverSolution:
    '''
    Propagate an orbit.

    Parameters
    ----------
    problem : Problem
        Problem structure.
    solver : Solver
        Solver structure.
    type : SolverType
        Type of solver.
    timestep : float
        Time step in seconds.
    tol : float
        Tolerance for error in metres.
    '''

    if solver in [RK4, RK45, RK810, RK1012]:
        solver_type = RK

    elif solver in [VERLET, YOSHIDA4, YOSHIDA8]:
        solver_type = SYMPLECTIC

    else:
        raise ValueError('Solver not supported.')

    casted_solver = cast_to_solver(ffi.addressof(solver))
    getLogger('hypernova').info('Propagating orbit...')
    start = perf_counter()
    solution = SolverSolution(propagate_orbit_c(
        problem, casted_solver, solver_type, timestep, tol))
    end = perf_counter()
    getLogger('hypernova').info(
        'Done. Time: {:.4f} seconds.'.format(end - start))

    return solution
