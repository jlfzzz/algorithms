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
    def numberOfPairs(self, points: List[List[int]]) -> int:
        points.sort(key=lambda p: (p[0], -p[1]))
        ans = 0
        for i, (_, y0) in enumerate(points):
            max_y = -inf
            for _, y in points[i + 1 :]:
                if max_y < y <= y0:
                    max_y = y
                    ans += 1
        return ans
    


# 这是错误的
class Solution:
    def numberOfPairs(self, points: List[List[int]]) -> int:
        points.sort(key=lambda a: (a[0], -a[1]))
        groups = []
        i = 0
        n = len(points)
        while i < n:
            x, y = points[i]
            temp = [(x, y)]
            j = i + 1
            while j < n and points[j][0] == x:
                temp.append((points[j][0], points[j][1]))
                j += 1
            groups.append(temp)
            i = j
        ans = 0
        for i, group in enumerate(groups):
            ans += len(group) - 1

            m1 = len(group)
            if i + 1 < len(groups):
                g2 = groups[i + 1]
                m2 = len(g2)
                p2 = 0
                for p1 in range(m1):
                    _, y1 = group[p1]
                    while p2 < m2 and g2[p2][1] > y1:
                        p2 += 1
                    if p2 != m2:
                        curr_g_next = -inf if p1 == m1 - 1 else group[p1 + 1][1]
                        if g2[p2][1] > curr_g_next:
                            ans += 1
        return ans
