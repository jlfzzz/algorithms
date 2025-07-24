from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
INF = int(1e9)


class Solution:
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        vals = [[i, nums[i]] for i in range(n)]  # 辅助数组
        # 按照数值降序排序
        vals.sort(key=lambda x: -x[1])
        # 取前 k 个并按照下标升序排序
        vals = sorted(vals[:k])
        res = [val for idx, val in vals]  # 目标子序列
        return res


class Solution:
    def maxSubsequence(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        dp = [[-inf]] * (k + 1)
        dp[0] = []
        for x in nums:
            for i in range(k, 0, -1):
                if sum(dp[i - 1]) + x > sum(dp[i]):
                    dp[i] = dp[i - 1][:]
                    dp[i].append(x)
        return dp[k]
