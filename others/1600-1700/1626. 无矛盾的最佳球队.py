import sys
import math
import bisect
import heapq
import collections
import functools
import itertools
import threading
from typing import List


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
