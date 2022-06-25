from supernova.supernova_c.lib import dot
import pytest
import numpy as np


def test_vector_math():
    u = [1, 2, 3]
    v = [4, 5, 6]

    result_np = np.dot(np.array(u), np.array(v))
    result_sn = dot(u, v)

    assert result_np == result_sn
