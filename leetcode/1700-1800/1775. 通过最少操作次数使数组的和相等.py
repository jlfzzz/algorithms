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
INF = float('inf')
MOD = int(1e9 + 7)


from collections import Counter
from typing import List

class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        n, m = len(nums1), len(nums2)
        if m * 6 < n or n * 6 < m:
            return -1

        s1, s2 = sum(nums1), sum(nums2)
        if s1 == s2:
            return 0

        if s1 < s2:
            nums1, nums2 = nums2, nums1
            s1, s2 = s2, s1

        diff = s1 - s2
        cnt1 = Counter(nums1)
        cnt2 = Counter(nums2)

        gain_count = [0] * 6 

        for i in range(1, 7):
            if i < 6:
                gain = 6 - i
                gain_count[gain] += cnt2[i]
            if i > 1:
                gain = i - 1
                gain_count[gain] += cnt1[i]

        ops = 0
        for gain in range(5, 0, -1):
            while gain_count[gain] > 0 and diff > 0:
                diff -= gain
                gain_count[gain] -= 1
                ops += 1
                if diff <= 0:
                    return ops

        return -1
