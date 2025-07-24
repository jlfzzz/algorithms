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


class Solution:
    def maxStrength(self, nums: List[int]) -> int:
        n = len(nums)
        mn, mx = nums[0], nums[0]
        ans = mx
        for i in range(1, n):
            x = nums[i]
            mn, mx = min(mn * x, mx * x, x, mn), max(mx * x, mn * x, x, mx)
            ans = max(ans, mx)
        return ans


class Solution:
    def maxStrength(self, nums: List[int]) -> int:
        n = len(nums)
        pre = [1] * (n + 1)
        for i in range(n):
            pre[i + 1] = pre[i] * nums[i]

        dp = [-inf] * (n + 1)
        dp[0] = 0
        for i in range(1, n + 1):
            for j in range(i):
                dp[i] = max(dp[i], dp[j] + pre[i] // pre[j])
        return dp[n]
