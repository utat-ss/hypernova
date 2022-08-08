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
""")


ffibuilder.set_source('supernova.supernova_c',  # name of the output C extension
                      '#include "vector_operations.h"\n'
                      '#include "adaptive_rk.h"\n'
                      '#include "solver_toy_problem.h"\n'
                      '#include "rk4.h"\n',
                      include_dirs=["supernova/src/vector_math",
                                    "supernova/src/solvers",
                                    "supernova/src/solvers/solver_configurations"],
                      sources=['supernova/src/vector_math/vector_operations.c',
                               'supernova/src/solvers/adaptive_rk.c',
                               'supernova/src/solvers/solver_toy_problem.c',
                               'supernova/src/solvers/solver_configurations/rk4.c'])
# TODO: link math library on unix based systems

if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
