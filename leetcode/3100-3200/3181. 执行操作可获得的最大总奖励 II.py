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
    def maxTotalReward(self, rewardValues: List[int]) -> int:
        f = 1
        for v in sorted(set(rewardValues)):
            f |= (f & ((1 << v) - 1)) << v
        return f.bit_length() - 1
