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


class Solution:
    def numberOfWays(self, n: int, x: int) -> int:
        f = [1] + [0] * n
        for i in range(1, n + 1):
            v = i**x
            if v > n:
                break
            for s in range(n, v - 1, -1):
                f[s] += f[s - v]
        return f[n] % 1_000_000_007
