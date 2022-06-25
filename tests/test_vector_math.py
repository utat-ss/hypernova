from supernova.supernova_c.lib import dot, cross
from supernova.supernova_c import ffi
import pytest
import numpy as np


def test_dot_product():
    u = [1, 2, 3]
    v = [4, 5, 6]

    result_np = np.dot(np.array(u), np.array(v))
    result_sn = dot(u, v)

    assert result_np == result_sn

def test_cross_product():
    u = [1, 2, 3]
    v = [4, 5, 6]

    result_np = np.cross(np.array(u), np.array(v))

    w = ffi.new("double[]", [0, 0, 0])
    cross(u, v, w)
    assert w[0] == pytest.approx(result_np[0])
    assert w[1] == pytest.approx(result_np[1])
    assert w[2] == pytest.approx(result_np[2])
