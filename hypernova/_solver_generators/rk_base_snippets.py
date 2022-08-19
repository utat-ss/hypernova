
rk_main_body = \
    '''
SolverSolution *{{solver_name}}_solve(ODEFunction f, Problem problem, double tol, double h0)
{
    /*
    * Solve the ODE y' = f(t, y) from t0 to t1 using an adaptive Runge-Kutta method.
    *
    * solver: the RKSolver to use
    * f: the ODE function to solve
    * problem: intial value problem to solve, inclding spacecraft information
    * tol: the desired error tolerance
    * h0: the initial step size
    *
    * Returns a SolverSolution struct containing the solution.
    */

    // Check for invalid inputs
    if (problem.t0 > problem.t1)
    {
        fprintf(stderr, "Error: t0 > t1\n");
        return NULL;
    }

    if (tol < 0)
    {
        fprintf(stderr, "Error: tol < 0\n");
        return NULL;
    }

    if (h0 <= 0)
    {
        fprintf(stderr, "Error: h0 <= 0\n");
        return NULL;
    }
    // Estimate number of steps required
    size_t n = (size_t)fmax(ceil((problem.t1 - problem.t0) * 86400 / h0), 10);
    size_t step = 0;

    // Initialize the solution struct
    SolverSolution *solution = malloc(sizeof(SolverSolution));
    solution->t = malloc(n * sizeof(double));
    solution->jd = malloc(n * sizeof(double));
    solution->y = malloc(n * sizeof(double[VEC_SIZE]));

    // Initialize step variables
    double h = h0;          // current step size, in seconds, initialized to h0
    double t = 0;           // elapsed time, in seconds
    double jd = problem.t0; // absolute mission time, in jd
    double y[VEC_SIZE];     // current state

    // Initialize the solution vector
    for (size_t i = 0; i < VEC_SIZE; i++)
    {
        solution->y[0][i] = problem.y0[i];
        y[i] = problem.y0[i];
    }
    solution->t[0] = t;
    solution->jd[0] = jd;

    // RK loop
    while (jd - h / 86400 < problem.t1)
    {
        // Compute the next step and get error estimate
        double e = {{solver_name}}_step(f, problem.spacecraft, t, jd, y, h);

        if (e < tol)
        {
            // accept step
            step++;
            t += h;
            jd += h / 86400;

            // double size of array and reallocate memory
            if (step >= n)
            {
                n *= 2;
                solution->y = (double(*)[6])realloc(solution->y, n * sizeof(double[VEC_SIZE]));
                solution->t = (double(*))realloc(solution->t, n * sizeof(double));
                solution->jd = (double(*))realloc(solution->jd, n * sizeof(double));
            }

            // copy new state into solution
            for (size_t i = 0; i < VEC_SIZE; i++)
            {
                solution->y[step][i] = y[i];
            }
            solution->t[step] = t;
            solution->jd[step] = jd;
        }
        // otherwise, reject step

        if (solver.is_adaptive)
        {
            // adapt step size
            double desired_next_step = 0.9 * h * pow(tol / e, 1.0 / (double)solver.order);
            // prevent step size from growing or shrinking too fast

            if (desired_next_step > 2 * h)
            {
                h = 2 * h;
            }
            else if (desired_next_step < 0.5 * h)
            {
                h = 0.5 * h;
            }
            else
            {
                h = desired_next_step;
            }
        }

        // prevent solver from overstepping the end of the time domain
        if (jd + h / 86400 > problem.t1)
        {
            h = (problem.t1 - jd) * 86400;
        }
    }
    solution->n = step;

    return solution;
}
'''

rk_step = \
    '''
inline double adaptive_rk_step(ODEFunction f, Spacecraft spacecraft,
                               double t, double jd, double y[VEC_SIZE], double h)
{
    double F[MAX_BUTCHER_TABLEAU_SIZE][VEC_SIZE]; // slopes at each stage
    double v[VEC_SIZE];                           // intermediate values at each stage

    // perform all stages
    for (size_t stage = 0; stage < {{num_stages}}; stage++)
    {
        for (size_t component = 0; component < VEC_SIZE; component++)
        {
            v[component] = y[component];
            for (size_t i = 0; i < stage; i++)
            {
                v[component] += h * F[i][component] * {{solver_name}}_A[stage][i];
            }
        }
        f(t + h * {{solver_name}}_C[stage], jd + (h * {{solver_name}}_C[stage]) / 86400, v, F[stage], spacecraft);
    }

    // advance solution
    for (size_t component = 0; component < VEC_SIZE; component++)
    {
        for (size_t stage = 0; stage < {{num_stages}}; stage++)
        {
            y[component] += h * F[stage][component] * {{solver_name}}_B[stage];
        }
    }

    // estimate error
    return fabs({{solver_name}}_error_correlation(h, F));
}
'''
