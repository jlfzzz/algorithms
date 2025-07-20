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
    def checkDivisibility(self, n: int) -> bool:
        s, m = 0, 1
        x = n
        while x:
            x, d = divmod(x, 10)
            s += d
            m *= d
        return n % (s + m) == 0
