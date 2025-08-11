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

pow2 = [1 for _ in range(1005)]
for i in range(1, 1005):
    pow2[i] = pow2[i - 1] * 2 % MOD


class Solution:
    def productQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        arr = []
        for i in range(n.bit_length()):
            if n >> i & 1:
                arr.append(i)

        arr = [0] + arr
        for i in range(1, len(arr)):
            arr[i] = arr[i] + arr[i - 1]

        ans = []
        for i, q in enumerate(queries):
            l, r = q[0] + 1, q[1] + 1
            ans.append(pow2[arr[r] - arr[l - 1]])
        return ans
