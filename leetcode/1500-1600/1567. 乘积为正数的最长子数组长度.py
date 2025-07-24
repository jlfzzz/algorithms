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
    def getMaxLen(self, nums: List[int]) -> int:
        cntPos = 0
        cntNeg = 0
        ans = 0
        for x in nums:
            if x == 0:
                cntPos, cntNeg = 0, 0
            elif x < 0:
                cntPos, cntNeg = cntNeg + 1 if cntNeg != 0 else 0, cntPos + 1
            else:
                cntPos, cntNeg = cntPos + 1, cntNeg + 1 if cntNeg != 0 else 0
            ans = max(ans, cntPos)
        return ans
