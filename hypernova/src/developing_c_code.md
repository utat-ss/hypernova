# Useful Commands and Tools for Developing C Code

## Building Package in-place
This is useful if you want to quickly rebuild the code without re-`pip install`-ing the entire package.

When you initially install hypernova, run

```
pip install -e .
```
The `-e` flag makes it editable in-place

Then, when you modify the C code, run 

```
python3 -m hypernova.build_c_code
```
to update the C code.

## Checking for Memory Leaks
Build the code directly using a C compiler and/or makefile. Use the `-g` flag when compiling with gcc to expose debugger symbols, then run with valgrind.

For example:
```
gcc -o main hypernova/src/solvers/adaptive_rk.c hypernova/src/solvers/solver_toy_problem.c -lm -g

valgrind ./main
```
was used when diagnosing array resizing problems in the adaptive RK solver