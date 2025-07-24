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
    def numberOfArrays(self, s: str, k: int) -> int:
        n = len(s)
        m = len(str(k))
        dp = [0] * (n + 1)
        dp[0] = 1

        for i in range(1, n + 1):
            c = s[i - 1]
            if c != "0" and 1 <= int(c) <= k:
                dp[i] = dp[i - 1]
            for j in range(max(1, i - m), i):
                t = s[j - 1 : i]
                if t[0] != "0" and 1 <= int(t) <= k:
                    dp[i] = (dp[i] + dp[j - 1]) % MOD
        return dp[-1]
