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
    def minStable(self, nums: List[int], maxC: int) -> int:
        n = len(nums)
        left_min = [n] * n
        intervals = [[1, 0]]  # 哨兵
        for i, x in enumerate(nums):
            # 计算以 i 为右端点的子数组 GCD
            for p in intervals:
                p[0] = gcd(p[0], x)
            # nums[i] 单独一个数作为子数组
            intervals.append([x, i])

            # 去重（合并 GCD 相同的区间）
            idx = 1
            for j in range(1, len(intervals)):
                if intervals[j][0] != intervals[j - 1][0]:
                    intervals[idx] = intervals[j]
                    idx += 1
            del intervals[idx:]

            # 由于我们添加了哨兵，intervals[1] 的 GCD >= 2 且最长，取其区间左端点作为子数组的最小左端点
            if len(intervals) > 1:
                left_min[i] = intervals[1][1]

        def check(upper: int) -> bool:
            c = maxC
            i = upper
            while i < n:
                if i - left_min[i] + 1 > upper:
                    if c == 0:
                        return False
                    c -= 1
                    i += upper + 1
                else:
                    i += 1
            return True

        return bisect_left(range(len(nums) // (maxC + 1)), True, key=check)
