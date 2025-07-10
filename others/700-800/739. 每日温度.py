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
MOD = int(1e9 + 7)


class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        dq = deque()
        n = len(temperatures)
        ans = [0] * n
        for i, x in enumerate(temperatures):
            while dq and x > temperatures[dq[-1]]:
                j = dq.pop()
                ans[j] = i - j
            dq.append(i)
        return ans


class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        dq = deque()
        ans = [0] * len(temperatures)
        for i in range(len(temperatures) - 1, -1, -1):
            t = temperatures[i]
            while dq and temperatures[dq[-1]] <= t:
                dq.pop()
            if dq:
                ans[i] = dq[-1] - i
            dq.append(i)
        return ans
