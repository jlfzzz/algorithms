from typing import List
from functools import cache


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        n = len(s)

        @cache
        def dfs(i: int) -> bool:
            if i == n:
                return True
            res = False
            for word in wordDict:
                m = len(word)
                if i + m <= n and s[i : i + m] == word:
                    res |= dfs(i + m)
            return res

        return dfs(0)


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        n = len(s)
        dp = [False] * (n + 1)
        dp[0] = True
        for i in range(n):
            for word in wordDict:
                m = len(word)
                if i - m + 1 >= 0 and s[i - m + 1 : i + 1] == word:
                    dp[i + 1] |= dp[i - m + 1]
        return dp[n]
