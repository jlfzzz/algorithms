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
    def maxOperations(self, nums: List[int]) -> int:
        n = len(nums)

        target = nums[0] + nums[-1]

        @cache
        def dfs(i: int, j: int):
            if i >= j:
                return 0

            res = 0
            if nums[i] + nums[j] == target:
                res = max(res, 1 + dfs(i + 1, j - 1))
            if i + 1 < j and nums[i + 1] + nums[i] == target:
                res = max(res, 1 + dfs(i + 2, j))
            if j - 1 > i and nums[j] + nums[j - 1] == target:
                res = max(res, 1 + dfs(i, j - 2))
            return res

        ans = dfs(0, n - 1)
        dfs.cache_clear()

        target = nums[0] + nums[1]
        ans = max(ans, dfs(0, n - 1))
        dfs.cache_clear()
        target = nums[-1] + nums[-2]
        ans = max(ans, dfs(0, n - 1))
        dfs.cache_clear()
        return ans
