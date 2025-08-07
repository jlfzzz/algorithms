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
    def earliestFinishTime(
        self,
        landStartTime: List[int],
        landDuration: List[int],
        waterStartTime: List[int],
        waterDuration: List[int],
    ) -> int:
        ans = inf
        for i, land in enumerate(landStartTime):
            end = land + landDuration[i]
            for j, water in enumerate(waterStartTime):
                if water >= end:
                    ans = min(ans, water + waterDuration[j])
                else:
                    ans = min(ans, end + waterDuration[j])

        for i, land in enumerate(waterStartTime):
            end = land + waterDuration[i]
            for j, water in enumerate(landStartTime):
                if water >= end:
                    ans = min(ans, water + landDuration[j])
                else:
                    ans = min(ans, end + landDuration[j])
        return ans
