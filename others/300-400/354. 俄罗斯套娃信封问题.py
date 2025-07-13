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
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        envelopes = sorted(envelopes, key=lambda x: (x[0], -x[1]))

        ans = []
        for _, y in envelopes:
            i = bisect_left(ans, y)
            if i == len(ans):
                ans.append(y)
            else:
                ans[i] = y
        return len(ans)
