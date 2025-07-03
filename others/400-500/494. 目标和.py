from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        offset = 1000  # 偏移量，防止负索引
        n = len(nums)
        dp = [0] * 2001
        dp[offset] = 1  # 和为0的情况计数为1

        for num in nums:
            new_dp = [0] * 2001
            for sum_idx in range(2001):
                if dp[sum_idx] != 0:
                    if sum_idx + num <= 2000:
                        new_dp[sum_idx + num] += dp[sum_idx]
                    if sum_idx - num >= 0:
                        new_dp[sum_idx - num] += dp[sum_idx]
            dp = new_dp

        return dp[target + offset] if -offset <= target <= offset else 0
