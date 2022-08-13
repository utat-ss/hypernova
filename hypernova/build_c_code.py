from cffi import FFI

ffibuilder = FFI()

ffibuilder.cdef("""
    double dot(double u[3], double v[3]);
    void cross(double u[3], double v[3], double w[3]);
    typedef struct SolverSolution
    {
        double *t;
        double *jd;
        double (*y)[6];
        size_t n;
    } SolverSolution;

    SolverSolution* solver_toy_problem_test();

    void free_solver_solution(SolverSolution *solution);

    typedef struct Spacecraft
    {
        double mass;
        double aerodynamic_area;
        double drag_coefficient;
    } Spacecraft;

    typedef struct Problem
    {
        double t0;
        double t1;
        Spacecraft spacecraft;
        double y0[6];
    } Problem;

    Problem initialize_problem(double t0, double t1, double y0[6], Spacecraft spacecraft);
    Spacecraft initialize_spacecraft(double mass);
    SolverSolution *propagate_orbit(Problem problem, double timestep);
""")


#  Any files with symbols exposed to CFFI or dependencies thereof must be
#  included below. Include both header and source files.
ffibuilder.set_source('hypernova.hypernova_c',  # name of the output C extension
                      '#include "vector_operations.h"\n'
                      '#include "solver_toy_problem.h"\n'
                      '#include "adaptive_rk.h"\n'
                      '#include "rk4.h"\n'
                      '#include "propagate_orbit.h"\n',
                      include_dirs=["hypernova/src/vector_math",
                                    "hypernova/src/solvers",
                                    "hypernova/src/solvers/solver_configurations",
                                    "hypernova/src/consolidations"],
                      sources=['hypernova/src/vector_math/vector_operations.c',
                               'hypernova/src/solvers/solver_toy_problem.c',
                               'hypernova/src/solvers/adaptive_rk.c',
                               'hypernova/src/solvers/solver_configurations/rk4.c',
                               'hypernova/src/consolidations/propagate_orbit.c',
                               'hypernova/src/physics/earth_gravity/simplified_gravity.c'],
                      extra_compile_args=['-std=c99', '-O3', '-march=native', '-ffast-math', "-lm"])
# TODO: link math library on unix based systems

if __name__ == "__main__":
    ffibuilder.compile(verbose=False)
