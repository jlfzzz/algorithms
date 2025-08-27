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
    def numberOfUniqueGoodSubsequences(self, binary: str) -> int:
        f0, f1 = 0, 0
        has0 = False
        for c in binary:
            if c == "1":
                f1 = (f0 + f1 + 1) % MOD
            else:
                f0 = (f0 + f1) % MOD
                has0 = True
        return (f0 + f1 + (1 if has0 else 0)) % MOD


class Solution:
    def numberOfUniqueGoodSubsequences(self, binary: str) -> int:
        f0, f1 = 0, 0
        has0 = False
        n = len(binary)
        for i in range(n - 1, -1, -1):
            if binary[i] == "1":
                f1 = (f1 + f0 + 1) % MOD
            else:
                f0 = (f1 + f0 + 1) % MOD
                has0 = True
        return f1 + has0
