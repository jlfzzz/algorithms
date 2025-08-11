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
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        n = len(arr)
        pre = [0 for _ in range(n + 1)]
        for i in range(1, n + 1):
            pre[i] = pre[i - 1] ^ arr[i - 1]

        ans = []
        for x in queries:
            a, b = x[0], x[1]
            ans.append(pre[b + 1] ^ pre[a])
        return ans
