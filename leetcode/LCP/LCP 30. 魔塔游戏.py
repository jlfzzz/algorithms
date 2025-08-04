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
    def magicTower(self, nums: List[int]) -> int:
        if sum(nums) + 1 <= 0:
            return -1

        curr = 1
        ans = 0
        h = []  # 小根堆存负数（最大负数在堆顶）

        for x in nums:
            curr += x
            if x < 0:
                heappush(h, x)
            if curr <= 0:
                # 当前血量已经不能活了，需要反悔之前最大的负数
                t = heappop(h)
                curr -= t  # 把它推迟（现在不吃了）
                ans += 1
        return ans
