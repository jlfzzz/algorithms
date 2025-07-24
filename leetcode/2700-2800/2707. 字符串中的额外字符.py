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
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:
        n = len(s)
        st = set(dictionary)

        @cache
        def dfs(i: int) -> int:
            if i == n:
                return 0

            # 选择1：跳过当前字符（作为额外字符）
            res = dfs(i + 1) + 1

            # 选择2：尝试匹配字典中的单词
            for j in range(i + 1, n + 1):
                if s[i:j] in st:
                    res = min(res, dfs(j))

            return res

        return dfs(0)


class Solution:
    def minExtraChar(self, s: str, dictionary: List[str]) -> int:
        n = len(s)
        st = set(dictionary)
        dp = [inf] * (n + 1)
        dp[0] = 0
        for i in range(1, n + 1):
            for j in range(1, i + 1):
                dp[i] = min(dp[j - 1] + i - j + 1, dp[i])
                if s[j - 1 : i] in st:
                    dp[i] = min(dp[i], dp[j - 1])
        return dp[n]
