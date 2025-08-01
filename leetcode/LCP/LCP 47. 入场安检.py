from typing import List

MOD = int(1e9 + 7)


class Solution:
    def securityCheck(self, capacities: List[int], k: int) -> int:
        dp = [0] * (k + 1)
        dp[0] = 1
        for i, x in enumerate(capacities):
            t = x - 1
            for j in range(k, t - 1, -1):
                dp[j] = (dp[j] + dp[j - t]) % MOD

        return dp[k]
