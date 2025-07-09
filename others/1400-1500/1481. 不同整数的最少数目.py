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
    def findLeastNumOfUniqueInts(self, arr: List[int], k: int) -> int:
        cnt = sorted(Counter(arr).values())
        s = 0
        j = 0
        for i, x in enumerate(cnt):
            s += x
            if s > k:
                j = i
                break   
            if s == k:
                j = i + 1
                break
        return len(cnt) - j