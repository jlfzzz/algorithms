from typing import List


class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)
        memo = [-1] * n

        def dfs(i: int) -> int:
            if i >= n:
                return 0

            if memo[i] != -1:
                return memo[i]

            res = max(dfs(i + 1), questions[i][0] + dfs(i + questions[i][1] + 1))
            memo[i] = res
            return res

        return dfs(0)


class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)
        dp = [0] * n

        for i in range(n - 1, -1, -1):
            res1 = dp[i + 1] if i + 1 < n else 0
            res2 = dp[i + questions[i][1] + 1] if i + questions[i][1] + 1 < n else 0
            dp[i] = max(res1, res2 + questions[i][0])

        return dp[0]


class Solution:
    def mostPoints(self, questions: List[List[int]]) -> int:
        n = len(questions)
        dp = [0] * (n + 1)

        for i, (x, y) in enumerate(questions):
            dp[i + 1] = max(dp[i + 1], dp[i])
            j = min(i + y + 1, n)
            dp[j] = max(dp[j], dp[i] + x)

        return dp[n]
