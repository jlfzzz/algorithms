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
    def getLeastFrequentDigit(self, n: int) -> int:
        cnt = defaultdict(int)
        while n:
            cnt[n % 10] += 1
            n //= 10
        mn = inf
        for a, b in cnt.items():
            if mn == inf:
                mn = a
            else:
                if (b < cnt[mn]) or (b == cnt[mn] and a < mn):
                    mn = a
        return mn
