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
    def profitableSchemes(
        self, n: int, minProfit: int, group: List[int], profit: List[int]
    ) -> int:
        m = len(profit)
        dp = [[[0] * (minProfit + 1) for _ in range(n + 1)] for _ in range(m + 1)]
        dp[0][0][0] = 1
        for i in range(1, m + 1):
            p, g = profit[i - 1], group[i - 1]
            for j in range(n, -1, -1):
                for k in range(minProfit, -1, -1):
                    dp[i][j][k] = dp[i - 1][j][k]
                    if j >= g:
                        # 如果k - p < 0，意味着加上当前的profit，总和一定大于k
                        # 所以直接加上0，也是单独取这么一个profit算一种
                        dp[i][j][k] = (
                            dp[i][j][k] + dp[i - 1][j - g][max(0, k - p)]
                        ) % MOD
        return sum(dp[m][j][minProfit] for j in range(n + 1)) % MOD
