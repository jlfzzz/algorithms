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
    def minOperations(self, nums: List[int]) -> int:
        ans = 0
        mx = 0
        for x in nums:
            cnt = 0
            while x:
                if x & 1:
                    ans += 1
                    x -= 1
                else:
                    cnt += 1
                    x >>= 1
            mx = max(mx, cnt)
        return ans + mx
