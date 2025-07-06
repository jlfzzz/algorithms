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
    def maxAlternatingSum(self, nums: List[int]) -> int:
        s1, s2 = 0, -inf
        for x in nums:
            s1, s2 = max(s1, s2 - x), max(s2, s1 + x)
        return max(s1, s2)
