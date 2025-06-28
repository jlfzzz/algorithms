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
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        k = len(strs)
        cnt = [[0, 0] for _ in range(k)]
        for i, s in enumerate(strs):
            cnt[i][0], cnt[i][1] = s.count("0"), s.count("1")

        dp = [[0] * (n + 1) for _ in range(m + 1)]

        for zeros, ones in cnt:
            for i in range(m, zeros - 1, -1):
                for j in range(n, ones - 1, -1):
                    dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1)

        return dp[m][n]
