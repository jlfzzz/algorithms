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
    def maxEvents(self, events: List[List[int]]) -> int:
        mx = max(e[1] for e in events)

        groups = [[] for _ in range(mx + 1)]
        for e in events:
            groups[e[0]].append(e[1])

        ans = 0
        h = []
        for i, g in enumerate(groups):
            while h and h[0] < i:
                heappop(h)
            for end_day in g:
                heappush(h, end_day)
            if h:
                ans += 1
                heappop(h)
        return ans
    