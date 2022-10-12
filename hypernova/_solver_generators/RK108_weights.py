import numpy as np
from scipy.sparse import coo_matrix

# Load RK weights from text file

# Load c values, starting from the 7th row and stopping after 17 rows
arrC = np.loadtxt("new_python/rk108.txt", skiprows=6, max_rows=17)
# This array is of shape (17, 2); the second column contains the RK C weights
C = arrC[:, 1]

# Load b values, starting from the 28th row and stopping after 17 rows
arrB = np.loadtxt("new_python/rk108.txt", skiprows=27, max_rows=17)
# This array is of shape (17, 2); the second column contains the RK B weights
B = arrB[:, 1]

# Load a values, starting from the 49th row and stopping at row 184
arrA = np.loadtxt("new_python/rk108.txt", skiprows=48, max_rows=134)
# This array is of shape (134, 3)
# The first two columns store the i, j indices corresponding to where the A weight is stored in a sparse matrix
# The third column stores the A weight
# construct the sparse matrix
A = coo_matrix((arrA[:, 2],
               (arrA[:, 0].astype(int),
                arrA[:, 1].astype(int))), shape=(17, 17)).toarray()
