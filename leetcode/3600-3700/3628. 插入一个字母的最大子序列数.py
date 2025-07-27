from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def numOfSubsequences(self, s: str) -> int:
        n = len(s)
        cnt1, cnt2, cnt3 = 0, 0, 0
        pairs = 0
        total = 0
        for i in range(n - 1, -1, -1):
            if s[i] == "L":
                cnt1 += 1
                total += pairs
            elif s[i] == "C":
                pairs += cnt3
                cnt2 += 1
            elif s[i] == "T":
                cnt3 += 1

        ans = total
        left1, left2 = 0, 0
        left_pairs = 0
        for i in range(0, n + 1):
            ans = max(ans, total + pairs)
            ans = max(ans, total + left1 * cnt3)
            ans = max(ans, total + left_pairs)
            if i != n:
                if s[i] == "L":
                    left1 += 1
                    cnt1 -= 1
                elif s[i] == "C":
                    left_pairs += left1
                    left2 += 1
                    cnt2 -= 1
                elif s[i] == "T":
                    cnt3 -= 1

        return ans
