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
    def maximumBags(
        self, capacity: List[int], rocks: List[int], additionalRocks: int
    ) -> int:
        arr = list(accumulate(sorted(x - y for x, y in zip(capacity, rocks))))
        return bisect_right(arr, additionalRocks)


class Solution:
    def maximumBags(
        self, capacity: List[int], rocks: List[int], additionalRocks: int
    ) -> int:
        arr = sorted([capacity[i] - rocks[i] for i in range(len(capacity))])
        i = 0
        while i < len(arr) and additionalRocks >= arr[i]:
            additionalRocks -= arr[i]
            i += 1
        return i
