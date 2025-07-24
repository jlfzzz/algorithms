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
    def checkDivisibility(self, n: int) -> bool:
        s = str(n)
        sum = 0
        prod = 1
        for c in s:
            sum += ord(c) - ord("0")
            prod *= ord(c) - ord("0")

        if n % sum == 0:
            return True
        if n % prod == 0:
            return True
        return False
