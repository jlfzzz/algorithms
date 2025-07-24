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
    def crackNumber(self, ciphertext: int) -> int:

        s = str(ciphertext)
        n = len(s)
        dp = [0] * (n + 1)
        dp[0] = 1
        for i in range(1, n + 1):
            x = int(str(s[i - 1 : i]))
            dp[i] = dp[i - 1]
            if i - 2 >= 0 and s[i - 2] != "0":
                x2 = int(str(s[i - 2 : i]))
                if 0 <= x2 <= 25:
                    dp[i] += dp[i - 2]
        return dp[n]
