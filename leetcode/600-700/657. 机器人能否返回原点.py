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
    def judgeCircle(self, moves: str) -> bool:
        dx, dy = 0, 0
        for c in moves:
            if c == "U":
                dy += 1
            elif c == "D":
                dy -= 1
            elif c == "L":
                dx -= 1
            else:
                dx += 1
        return dx == dy == 0
