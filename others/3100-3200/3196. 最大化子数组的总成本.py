from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *


MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
class Solution:
    def maximumTotalCost(self, a: List[int]) -> int:
        n = len(a)
        f = [0] * (n + 1)
        f[1] = a[0]
        for i in range(1, n):
            f[i + 1] = max(f[i] + a[i], f[i - 1] + a[i - 1] - a[i])
        return f[n]


class Solution:
    def maximumTotalCost(self, a: List[int]) -> int:
        f0, f1 = 0, a[0]
        for i in range(1, len(a)):
            f0, f1 = f1, max(f1 + a[i], f0 + a[i - 1] - a[i])
        return f1
