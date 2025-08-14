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

pow3 = [1 for _ in range(30)]
for i in range(1, 30):
    pow3[i] = pow3[i - 1] * 3


class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        st = set()
        while n:
            i = bisect_right(pow3, n) - 1
            if i in st:
                return False
            n -= pow3[i]
            st.add(i)
        return True
