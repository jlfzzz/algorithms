from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


MOD = int(1e9 + 7)


class Solution:
    def countPalindromicSubsequences(self, s: str) -> int:
        n = len(s)
        dp = [[0] * n for _ in range(n)]

        for i in range(n):
            dp[i][i] = 1
            for j in range(i - 1, -1, -1):
                if s[i] == s[j]:
                    l, r = j + 1, i - 1
                    while l <= r and s[l] != s[i]:
                        l += 1
                    while l <= r and s[r] != s[i]:
                        r -= 1
                    if l > r:
                        dp[j][i] = dp[j + 1][i - 1] * 2 + 2
                    elif l == r:
                        dp[j][i] = dp[j + 1][i - 1] * 2 + 1
                    else:
                        dp[j][i] = dp[j + 1][i - 1] * 2 - dp[l + 1][r - 1]
                else:
                    dp[j][i] = dp[j + 1][i] + dp[j][i - 1] - dp[j + 1][i - 1]

                dp[j][i] = (dp[j][i] + MOD) % MOD

        return dp[0][n - 1]
