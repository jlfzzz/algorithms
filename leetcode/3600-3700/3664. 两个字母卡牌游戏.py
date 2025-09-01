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
    def score(self, cards: List[str], x: str) -> int:
        cnt1 = [0] * 26
        cnt2 = [0] * 26
        cntx = 0
        for s in cards:
            if x in s:
                if s[0] == x and s[1] == x:
                    cntx += 1
                elif s[0] == x:
                    cnt1[ord(s[1]) - ord("a")] += 1
                else:
                    cnt2[ord(s[0]) - ord("a")] += 1

        ans = 0
        for choose1 in range(min(cntx, sum(cnt1)) + 1):
            sum1 = sum(cnt1) + choose1
            mx1 = max(cnt1)

            total1 = min(sum1 - mx1, sum1 // 2)

            sum2 = sum(cnt2) + min(cntx - choose1, sum(cnt2))
            mx2 = max(cnt2)

            total2 = min(sum2 - mx2, sum2 // 2)
            ans = max(ans, total1 + total2)

        return ans
