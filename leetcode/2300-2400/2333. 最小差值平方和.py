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
    def minSumSquareDiff(
        self, nums1: List[int], nums2: List[int], k1: int, k2: int
    ) -> int:
        n = len(nums1)
        diff = [0] * n
        ans = 0
        for i, (a, b) in enumerate(zip(nums1, nums2)):
            diff[i] = abs(a - b)
            ans += diff[i] * diff[i]

        diff.sort(reverse=True)
        total = k1 + k2
        prev = diff[0]
        i = 0
        while total > 0 and prev > 0:
            while i < n and diff[i] == prev:
                i += 1

            next_val = diff[i] if i < n else 0
            need = i * (prev - next_val)

            if total >= need:
                total -= need
                ans -= (prev * prev - next_val * next_val) * i
                prev = next_val
            else:
                extra = total % i
                mn = total // i
                t = prev - mn - 1
                ans -= (prev * prev - t * t) * extra
                t2 = prev - mn
                ans -= (prev * prev - t2 * t2) * (i - extra)
                total = 0

        return ans
