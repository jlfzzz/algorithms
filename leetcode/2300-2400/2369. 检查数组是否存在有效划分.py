from typing import List
from functools import cache


class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)

        @cache
        def dfs(i: int) -> bool:
            if i > n:
                return False
            if i == n:
                return True
            res = False
            if i + 1 < n and nums[i] == nums[i + 1]:
                res |= dfs(i + 2)
                if i + 2 < n and nums[i] == nums[i + 2]:
                    res |= dfs(i + 3)
            if i + 2 < n and (
                (nums[i] == nums[i + 1] - 1 and nums[i + 1] == nums[i + 2] - 1)
            ):
                res |= dfs(i + 3)
            return res

        return dfs(0)


class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        dp = [False] * (n + 1)
        dp[0] = True
        for i, x in enumerate(nums):
            res = False
            if i - 1 >= 0 and nums[i - 1] == nums[i]:
                res |= dp[i - 1]
                if i - 2 >= 0 and nums[i - 2] == nums[i]:
                    res |= dp[i - 2]
            if (
                i - 2 >= 0
                and nums[i - 2] == nums[i - 1] - 1
                and nums[i] - 1 == nums[i - 1]
            ):
                res |= dp[i - 2]
            dp[i + 1] = res
        return dp[n]
