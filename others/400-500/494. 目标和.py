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
        s = sum(nums) - abs(target)
        if s % 2 or s < 0:
            return 0

        m = s // 2

        def count(nums: List[int]) -> Dict[int, int]:
            cnt = defaultdict(int)
            for i in range(1 << len(nums)):
                s = sum(x for j, x in enumerate(nums) if i >> j & 1)
                cnt[s] += 1
            return cnt

        k = len(nums) // 2
        cnt1 = count(nums[:k])
        cnt2 = count(nums[k:])

        return sum(c1 * cnt2[m - x] for x, c1 in cnt1.items())


class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        offset = 1000  # 偏移量，防止负索引
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
