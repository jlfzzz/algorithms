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
    def numDecodings(self, s: str) -> int:
        n = len(s)
        dp = [0] * (n + 1)
        dp[0] = 1
        t = [str(x) for x in range(1, 27)]
        st = set(t)
        for i in range(1, n + 1):
            for j in range(max(0, i - 2), i):
                if s[j:i] in st:
                    dp[i] += dp[j]
        return dp[n]
