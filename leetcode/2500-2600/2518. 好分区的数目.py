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
    def countPartitions(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = pow(2, n, MOD)
        total = sum(nums)
        if total // 2 < k:
            return 0
        dp = [0] * (k)
        dp[0] = 1
        for x in nums:
            for i in range(k - 1, x - 1, -1):
                dp[i] = (dp[i] + dp[i - x]) % MOD

        for i in range(k):
            ans = (ans + MOD - dp[i] * 2) % MOD
        return ans
