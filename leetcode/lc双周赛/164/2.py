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

        p1 = 0
        total1 = sum(cnt1)
        if total1 > 0:
            max1 = max(cnt1)
            p1 = min(total1 - max1, total1 // 2)

        p2 = 0
        total2 = sum(cnt2)
        if total2 > 0:
            max2 = max(cnt2)
            p2 = min(total2 - max2, total2 // 2)

        rem1 = total1 - 2 * p1
        rem2 = total2 - 2 * p2

        p3 = min(cntx, rem1 + rem2)

        ans = p1 + p2 + p3
        return ans
