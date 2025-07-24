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
    def findSmallestSetOfVertices(self, n: int, edges: List[List[int]]) -> List[int]:
        deg = [0] * n
        ans = []
        for a, b in edges:
            deg[b] += 1
        for i, x in enumerate(deg):
            if x == 0:
                ans.append(i)
        return ans
