from typing import List

MOD = int(1e9 + 7)


class Solution:
    def sumOfPower(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ans = 0
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1

        for i in range(1, n + 1):
            for j in range(k + 1):
                dp[i][j] = (dp[i - 1][j] * 2) % MOD
                if j >= nums[i - 1]:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % MOD

        return dp[n][k]
