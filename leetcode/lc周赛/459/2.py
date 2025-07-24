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
    def countTrapezoids(self, points: List[List[int]]) -> int:
        points.sort(key=lambda x: x[1])
        s = 0
        n = len(points)

        i = 0
        ans = 0
        while i < n:
            j = i + 1
            y = points[y][1]
            while j < n and points[j][1] == y:
                j += 1

            curr = j - i
            curr = curr * (curr - 1) // 2
            ans = (ans + curr * s) % MOD
            s += curr
        return ans
