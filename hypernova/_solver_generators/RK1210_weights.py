import numpy as np
from scipy.sparse import coo_matrix

# Load RK weights from text file

# Load c values, starting from the 6th row and stopping after 25 rows
arrC = np.loadtxt("new_python/rk1210.txt", skiprows=5, max_rows=25)
# This array is of shape (25, 2); the second column contains the RK C weights
C = arrC[:, 1]

# Load b values, starting from the 34th row and stopping after 25 rows
arrB = np.loadtxt("new_python/rk1210.txt", skiprows=33, max_rows=25)
# This array is of shape (25, 2); the second column contains the RK B weights
B = arrB[:, 1]

# Load a values, starting from the 63rd row and stopping at row 362
arrA = np.loadtxt("new_python/rk1210.txt", skiprows=62, max_rows=300)
# This array is of shape (300, 3)
# The first two columns store the i, j indices corresponding to where the A weight is stored in a sparse matrix
# The third column stores the A weight
# construct the sparse matrix
A = coo_matrix((arrA[:, 2],
               (arrA[:, 0].astype(int),
                arrA[:, 1].astype(int))), shape=(25, 25)).toarray()
