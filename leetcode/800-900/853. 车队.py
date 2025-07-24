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
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        dq = deque()
        n = len(position)
        time = [0] * n
        for i, (p, t) in enumerate(sorted(zip(position, speed))):
            time[i] = (target - p) / t

        for i, x in enumerate(time):
            while dq and x >= time[dq[-1]]:
                dq.pop()
            dq.append(i)
        return len(dq)
