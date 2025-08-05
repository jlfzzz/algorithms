from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def closestRoom(
        self, rooms: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        n = len(rooms)
        k = len(queries)
        ans = [-1] * k

        new_queries = [(x[0], x[1], i) for i, x in enumerate(queries)]
        new_queries.sort(key=lambda x: x[1])
        lst = SortedList()
        rooms.sort(key=lambda x: x[1])

        j = n - 1
        for i in range(k - 1, -1, -1):
            preferred, minSize, index = new_queries[i]
            while j >= 0 and rooms[j][1] >= minSize:
                lst.add(rooms[j][0])
                j -= 1
            idx = lst.bisect_left(preferred)
            best_dist = float("inf")
            best_id = -1
            for l in range(max(0, idx - 1), min(idx + 2, len(lst))):
                dist = abs(preferred - lst[l])
                if dist < best_dist or (dist == best_dist and lst[l] < best_id):
                    best_dist = dist
                    best_id = lst[l]
            ans[index] = best_id
        return ans
