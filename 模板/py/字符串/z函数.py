from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def get_z(self, s: str) -> List[int]:
        n = len(s)
        z = [0] * n
        l, r = 0, 0
        ans = 0
        for i in range(1, n):
            if i <= r:
                z[i] = min(r - i + 1, z[i - l])
            while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                l, r = i, i + z[i] - 1
                z[i] += 1
        return z
