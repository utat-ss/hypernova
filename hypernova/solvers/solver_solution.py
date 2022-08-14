from hypernova.hypernova_c.lib import free_solver_solution as free_solver_solution_c
from hypernova.hypernova_c import ffi
import numpy as np

class SolverSolution:
    '''
    Wrapper for solver solution class which incorporates numpy arrays.

    Also allows for automatic freeing of memory.

    Initialized from cffi pointer.

    Parameters
    ----------
    t : numpy.ndarray
        mission elapsed time in seconds
    jd : numpy.ndarray
        absolute time in julian days
    y : numpy.ndarray
        state vector (x, y, z, vx, vy, vz) in meters and meters/second
    n : int
        number of steps in solution
    '''
    def __init__(self, pointer):
        self.pointer = pointer
    
    def __del__(self):
        # automatically free memory
        free_solver_solution_c(self.pointer)

    @property
    def n(self):
        return self.pointer.n

    @property
    def t(self):
        t = np.frombuffer(ffi.buffer(self.pointer.t, self.pointer.n *
                        ffi.sizeof("double")), dtype=np.double)
        t.shape = (self.pointer.n, 1)
        return t

    @property 
    def jd(self):
        jd = np.frombuffer(ffi.buffer(self.pointer.jd, self.pointer.n *
                        ffi.sizeof("double")), dtype=np.double)
        jd.shape = (self.pointer.n, 1)
        return jd

    @property
    def y(self):
        y = np.frombuffer(ffi.buffer(self.pointer.y, self.pointer.n *
                        6 * ffi.sizeof("double")), dtype=np.double)
        y.shape = (self.pointer.n, 6)
        return y
