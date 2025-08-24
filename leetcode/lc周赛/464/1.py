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
    def gcdOfOddEvenSums(self, n: int) -> int:
        sum1 = 0
        i = 1
        for j in range(n):
            sum1 += i
            i += 2
        i = 2
        sum2 = 0
        for j in range(n):
            sum2 += i
            i += 2

        return gcd(sum1, sum2)
