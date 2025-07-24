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
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def minHeightShelves(self, books: List[List[int]], shelfWidth: int) -> int:
        n = len(books)

        @cache
        def dfs(i: int) -> int:
            if i == n:
                return 0

            res = 10000000000
            j = i
            max_h = 0
            curr = 0
            while j < n and curr + books[j][0] <= shelfWidth:
                curr += books[j][0]
                max_h = max(max_h, books[j][1])
                t = dfs(j + 1) + max_h
                if t < res:
                    res = t
                j += 1
            return res

        return dfs(0)
