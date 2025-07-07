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
    def minimumBoxes(self, apple: List[int], capacity: List[int]) -> int:
        capacity.sort(key=lambda x: -x)
        s = sum(apple)
        i = 0
        curr = 0
        while i < len(capacity):
            curr += capacity[i]
            i += 1
            if curr >= s:
                break

        return i
