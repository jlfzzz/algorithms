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
    def distinctSubseqII(self, s: str) -> int:
        last = defaultdict(int)
        n = len(s)
        dp = [0] * (n + 1)
        dp[0] = 1
        for i in range(1, n + 1):
            dp[i] = dp[i - 1] * 2 % MOD
            c = s[i - 1]
            if c in last:
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD
            last[c] = i
        return (dp[n] - 1 + MOD) % MOD


class Solution:
    def distinctSubseqII(self, s: str) -> int:
        f = [[0] * 26 for _ in range(len(s) + 1)]
        for i, c in enumerate(s):
            c = ord(c) - ord("a")
            f[i + 1] = f[i].copy()
            f[i + 1][c] = (1 + sum(f[i])) % MOD
        return sum(f[-1]) % MOD
