from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:
        pairs = [[x, y] for x, y in zip(ages, scores)]
        pairs.sort()
        dp = [0] * len(scores)

        for i in range(len(pairs)):
            a, b = pairs[i]  
            dp[i] = b
            for j in range(i):
                x, y = pairs[j]
                if b >= y:  # 当前球员得分 >= 之前球员得分，无冲突
                    dp[i] = max(dp[i], dp[j] + b)

        return max(dp)  # 返回所有dp值的最大值


class Solution:
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:
        n = len(scores)
        pairs = list(zip(ages, scores))

        pairs.sort()
        dp = [0] * n
        ans = 0

        for i in range(n):
            dp[i] = pairs[i][1]
            for j in range(i):
                if pairs[j][1] <= pairs[i][1]:
                    dp[i] = max(dp[i], dp[j] + pairs[i][1])
            ans = max(ans, dp[i])

        return ans
