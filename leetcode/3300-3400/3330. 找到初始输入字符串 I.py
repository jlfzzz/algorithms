from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def possibleStringCount(self, word: str) -> int:
        ans = 1
        for x, y in pairwise(word):
            if x == y:
                ans += 1
        return ans
