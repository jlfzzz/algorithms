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
        lo = 0
        hi = n + 1

        def check(limit: int) -> bool:
            use = 0
            hcd = nums[0]
            left = 0
            for i in range(1, n):
                x = nums[i]
                hcd = gcd(hcd, x)
                if hcd == 1:
                    if i + 1 == n:
                        break
                    left = i + 1
                    hcd = nums[i + 1]
                    continue
                if i - left + 1 > limit:
                    if use == maxC:
                        return False
                    if i + 1 == n:
                        break
                    left = i + 1
                    hcd = nums[i + 1]
                    continue
            return True

        ans = n
        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                ans = mid
                hi = mid
            else:
                lo = mid + 1
        return ans
