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
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        n = len(nums1)
        ans = [-1] * n

        dq = deque()
        nxt = defaultdict()
        for i, x in enumerate(nums2):
            while dq and nums2[dq[-1]] < x:
                y = dq.pop()
                nxt[nums2[y]] = x
            dq.append(i)

        for i, x in enumerate(nums1):
            if x in nxt:
                ans[i] = nxt[x]
        return ans
