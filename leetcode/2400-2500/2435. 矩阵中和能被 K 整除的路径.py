from typing import List


MOD = int(1e9 + 7)


class Solution:
    def numberOfPaths(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])

        dp = [[[0] * k for _ in range(n + 1)] for _ in range(m + 1)]
        dp[1][0][0] = 1

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                for l in range(k):
                    dp[i][j][(l + grid[i - 1][j - 1]) % k] = (
                        dp[i - 1][j][l] + dp[i][j - 1][l]
                    ) % MOD

        return dp[m][n][0]
