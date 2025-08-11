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
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


MOD = 10
MX = 100_000

f = [0] * (MX + 1)
inv_f = [0] * (MX + 1)
p2 = [0] * (MX + 1)
p5 = [0] * (MX + 1)

f[0] = 1
for i in range(1, MX + 1):
    x = i
    # 计算 2 的幂次
    e2 = (x & -x).bit_length() - 1
    x >>= e2
    # 计算 5 的幂次
    e5 = 0
    while x % 5 == 0:
        e5 += 1
        x //= 5
    f[i] = f[i - 1] * x % MOD
    p2[i] = p2[i - 1] + e2
    p5[i] = p5[i - 1] + e5

inv_f[MX] = pow(f[MX], 3, MOD)  # 欧拉定理求逆元
for i in range(MX, 0, -1):
    x = i
    x >>= (x & -x).bit_length() - 1
    while x % 5 == 0:
        x //= 5
    inv_f[i - 1] = inv_f[i] * x % MOD


def comb(n: int, k: int) -> int:
    # 由于每项都 < 10，所以无需中途取模
    return (
        f[n]
        * inv_f[k]
        * inv_f[n - k]
        * pow(2, p2[n] - p2[k] - p2[n - k], MOD)
        * pow(5, p5[n] - p5[k] - p5[n - k], MOD)
    )


class Solution:
    def hasSameDigits(self, s: str) -> bool:
        n = len(s)
        s = map(ord, s)
        return (
            sum(comb(n - 2, i) * (x - y) for i, (x, y) in enumerate(pairwise(s))) % MOD
            == 0
        )
