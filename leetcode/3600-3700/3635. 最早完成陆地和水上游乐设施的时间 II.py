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
        land = [(x, y) for (x, y) in zip(landStartTime, landDuration)]
        water = [(x, y) for (x, y) in zip(waterStartTime, waterDuration)]

        land.sort(key=lambda x: x[0])
        water.sort(key=lambda x: x[0])

        def f(arr1, arr2) -> int:
            mx = -inf
            for i, (x, y) in enumerate(arr2):
                mx = Max(mx, x + y)

            pre = [inf] * (int(mx + 100))
            for i in range(len(arr2)):
                pre[arr2[i][0]] = Min(arr2[i][1], pre[arr2[i][0]])

            for i in range(1, int(mx + 10)):
                pre[i] = Min(pre[i], pre[i - 1])

            ans = inf
            j = len(arr2) - 1
            right = inf
            for i in range(len(arr1) - 1, -1, -1):
                start, duration = arr1[i][0], arr1[i][1]
                while j >= 0 and arr2[j][0] >= start + duration:
                    right = Min(right, arr2[j][0] + arr2[j][1])
                    j -= 1
                ans = Min(ans, Min(start + duration + pre[start + duration], right))
            return ans

        return Min(f(land, water), f(water, land))
