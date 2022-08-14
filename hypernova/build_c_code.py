from cffi import FFI
import os

ffibuilder = FFI()

ffibuilder.cdef("""
    // vector math
    double dot(double u[3], double v[3]);
    void cross(double u[3], double v[3], double w[3]);

    // solver abstractions
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

    typedef struct ButcherTableau
    {
        double (*A)[25]; // Derivative weights
        double(*b);                            // Next step weights
        double(*c);                            // Evaluation positions
    } ButcherTableau;

    typedef struct SymplecticSolver
    {
        // Weights
        double(*c);
        double(*d);
        size_t num_stages;
    } SymplecticSolver;

    // typedef for error correlation
    typedef double (*RKErrorCorrelation)(double h, double F[25][6]);

    typedef struct RKSolver
    {
        ButcherTableau weights;
        RKErrorCorrelation err_corr;
        bool is_adaptive;
        size_t num_stages;
        size_t order;
    } RKSolver;

    typedef union Solver
    {
        RKSolver rk;
        SymplecticSolver symplectic;
    } Solver;

    enum SolverType
    {
        RK,
        SYMPLECTIC
    };

    Solver cast_to_solver(void *solver);

    Problem initialize_problem(double t0, double t1, double y0[6], Spacecraft spacecraft);
    Spacecraft initialize_spacecraft(double mass);
    SolverSolution *propagate_orbit(Problem problem, Solver solver, enum SolverType type, double timestep, double tol);

    // solvers
    RKSolver rk4();
    RKSolver rk45();
    SymplecticSolver verlet();
    SymplecticSolver yoshida4();
    SymplecticSolver yoshida8();
    """)

# Walk through the directory and find all the .c files
files = []
include_dirs = set()
for dirpath, dirnames, filenames in os.walk('hypernova/src'):
    for filename in filenames:
        if filename.endswith('.c'):
            files.append(os.path.join(dirpath, filename))
            include_dirs.add(dirpath)

#  Any symbols exposed by CFFI must be included in the first argument of set_source.
ffibuilder.set_source('hypernova.hypernova_c',  # name of the output C extension
                      '#include "vector_operations.h"\n'
                      '#include "solver_abstractions.h"\n'
                      '#include "solver_toy_problem.h"\n'
                      '#include "solver_configurations.h"\n'
                      '#include "propagate_orbit.h"\n',
                      include_dirs=list(include_dirs),
                      sources=files,
                      extra_compile_args=['-std=c99', '-O3', '-march=native', '-ffast-math', "-lm"])
# TODO: link math library on unix based systems

if __name__ == "__main__":
    ffibuilder.compile(verbose=False)
