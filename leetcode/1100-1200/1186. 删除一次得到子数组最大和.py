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
    def maximumSum(self, arr: List[int]) -> int:
        f0, f1 = arr[0], -inf
        ans = -inf
        for i in range(1, len(arr)):
            x = arr[i]
            f0, f1 = max(f0 + x, x), max(f1 + x, f0)
            ans = max(ans, f0, f1)
        return ans
