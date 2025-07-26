from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        a = sorted((x, y, i) for i, (x, y) in enumerate(zip(nums1, nums2)))

        n = len(a)
        ans = [0] * n
        h = []
        # 分组循环模板
        s = i = 0
        while i < n:
            start = i
            x = a[start][0]
            # 找到所有相同的 nums1[i]，这些数的答案都是一样的
            while i < n and a[i][0] == x:
                ans[a[i][2]] = s
                i += 1
            # 把这些相同的 nums1[i] 对应的 nums2[i] 入堆
            for j in range(start, i):
                y = a[j][1]
                s += y
                heappush(h, y)
                if len(h) > k:
                    s -= heappop(h)
        return ans
