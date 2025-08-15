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
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def numberOfPermutations(self, n: int, requirements: List[List[int]]) -> int:
        req = {end: inv for end, inv in requirements}
        if 0 in req and req[0]:
            return 0
        max_k = 400

        dp = [0] * (max_k + 1)
        dp[0] = 1

        for i in range(2, n + 1):
            next_dp = [0] * (max_k + 1)
            sm = 0

            for j in range(max_k + 1):
                sm = (sm + dp[j]) % MOD

                if j >= i:
                    sm = (sm - dp[j - i] + MOD) % MOD

                next_dp[j] = sm

            if (i - 1) in req:
                req_k = req[i - 1]
                for j in range(max_k + 1):
                    if j != req_k:
                        next_dp[j] = 0

            dp = next_dp

        return dp[req.get(n - 1)]
