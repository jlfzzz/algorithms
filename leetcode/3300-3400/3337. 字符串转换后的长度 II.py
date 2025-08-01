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
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD

    return res


MOD = 1_000_000_007


# a @ b，其中 @ 是矩阵乘法
def mul(a: List[List[int]], b: List[List[int]]) -> List[List[int]]:
    return [
        [sum(x * y for x, y in zip(row, col)) % MOD for col in zip(*b)] for row in a
    ]


# a^n @ f0
def pow_mul(a: List[List[int]], n: int, f0: List[List[int]]) -> List[List[int]]:
    res = f0
    while n:
        if n & 1:
            res = mul(a, res)
        a = mul(a, a)
        n >>= 1
    return res


class Solution:
    def lengthAfterTransformations(self, s: str, t: int, nums: List[int]) -> int:
        SIZE = 26
        f0 = [[1] for _ in range(SIZE)]
        m = [[0] * SIZE for _ in range(SIZE)]
        for i, c in enumerate(nums):
            for j in range(i + 1, i + c + 1):
                m[i][j % SIZE] = 1
        mt = pow_mul(m, t, f0)

        ans = 0
        for ch, cnt in Counter(s).items():
            ans += mt[ord(ch) - ord("a")][0] * cnt
        return ans % MOD
