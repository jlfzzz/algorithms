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
    def numDecodings(self, s: str) -> int:
        n = len(s)
        st = [str(x) for x in range(1, 27)]
        st = set(st)
        dp = [0] * (n + 1)
        dp[0] = 1
        for i in range(1, n + 1):
            c = s[i - 1]
            if c == "*":
                dp[i] = (dp[i - 1] * 9) % MOD
                if i - 2 >= 0:
                    if s[i - 2] == "2":
                        dp[i] = (dp[i] + 6 * dp[i - 2]) % MOD
                    elif s[i - 2] == "1":
                        dp[i] = (dp[i] + 9 * dp[i - 2]) % MOD
                    elif s[i - 2] == "*":
                        dp[i] = (dp[i] + 15 * dp[i - 2]) % MOD
            elif c == "0":
                if i - 2 >= 0:
                    cc = s[i - 2]
                    if cc == "*":
                        dp[i] = (dp[i - 2] * 2) % MOD
                    else:
                        if s[i - 2 : i] in st:
                            dp[i] = dp[i - 2]
            else:
                dp[i] = dp[i - 1]
                if i - 2 >= 0:
                    if s[i - 2] == "*":
                        if (
                            c == "1"
                            or c == "2"
                            or c == "3"
                            or c == "4"
                            or c == "5"
                            or c == "6"
                        ):
                            dp[i] = (dp[i] + dp[i - 2] * 2) % MOD
                        else:
                            dp[i] = (dp[i] + dp[i - 2]) % MOD
                    elif s[i - 2 : i] in st:
                        dp[i] = (dp[i] + dp[i - 2]) % MOD
        return dp[n]
