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

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:
        cnt = defaultdict(int)
        for x, y in zip(basket1, basket2):
            cnt[x] += 1
            cnt[y] += 1
        for v in cnt.values():
            if v & 1:
                return -1

        cnt1 = Counter(basket1)
        cnt2 = Counter(basket2)

        v1, v2 = [], []

        for k, v in cnt.items():
            d = v // 2 - cnt1[k]
            for _ in range(abs(d)):
                if d > 0:
                    v1.append(k)  # basket1 缺 -> 需要加入
                else:
                    v2.append(k)  # basket2 缺 -> 需要加入

        v1.sort()
        v2.sort()
        m = len(v1)
        ans = 0
        min_val = min(cnt.keys())

        for i in range(m):
            a = v1[i]
            b = v2[m - 1 - i]
            ans += min(min(a, b), 2 * min_val)
        return ans
