# Manipulating Arrays
You can do some pretty terrible things with arrays in C.

## Forcing a 1D array into a 2D array using evil pointer arithmetic
Consider the 1D array:
```c
int foo[] = {1,2,3,4,5,6};
```

You can turn this into a 2D array by doing this:
```c
int (*bar)[3] = (int (*)[3])&foo[0];
```

Source: https://stackoverflow.com/questions/12692310/convert-array-to-two-dimensional-array-by-pointer

## 2D array pointer types
2D arrays of doubles should be declared as:
```c
double (*foo)[COLUMNS];
```

Memory should be allocated as:
```c
foo = malloc(ROWS * sizeof(double[COLUMNS]));
```

Note that the pointer type is `double (*)[COLUMNS]`. This is needed for function declarations.