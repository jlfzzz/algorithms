from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


def mat_mul(a: List[List[int]], b: List[List[int]]) -> List[List[int]]:
    n, p = len(a), len(a[0])
    p2, m = len(b), len(b[0])
    assert p == p2, "Matrix dimensions do not match for multiplication"
    res = [[0] * m for _ in range(n)]

    for i in range(n):
        for k in range(p):
            for j in range(m):
                res[i][j] += a[i][k] * b[k][j]

    return res


def mat_pow(a: List[List[int]], n: int) -> List[List[int]]:
    size = len(a)
    # 初始化为单位矩阵
    res = [[0] * size for _ in range(size)]
    for i in range(size):
        res[i][i] = 1

    base = a
    while n > 0:
        if n & 1:
            res = mat_mul(res, base)
        base = mat_mul(base, base)
        n >>= 1
    return res


class Solution:
    def fib(self, n: int) -> int:
        if n == 0:
            return 0
        # 转移矩阵
        mat = [[1, 1], [1, 0]]
        # 初始状态向量 F(1) = 1, F(0) = 0
        f0 = [[1], [0]]
        res = mat_pow(mat, n - 1)
        res = mat_mul(res, f0)
        return res[0][0]  # F(n)
