from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
MOD = int(1e9 + 7)


class Solution:
    def countDays(self, days: int, meetings: List[List[int]]) -> int:
        meetings.sort()
        prev = 1
        ans = 0
        for a, b in meetings:
            if a > prev:
                ans += a - prev
            if b >= prev:
                prev = b + 1
        if days >= prev:
            ans += days - prev + 1
        return ans
