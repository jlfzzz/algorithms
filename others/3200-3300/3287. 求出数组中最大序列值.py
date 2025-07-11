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
    def maxValue(self, nums: List[int], k: int) -> int:
        mx = max(nums)
        m = mx.bit_length()
        n = len(nums)

        def f(nums: List[int]):
            dp1 = [[[False] * (1 << m) for _ in range(k + 1)] for _ in range(n + 1)]
            dp1[0][0][0] = True
            for i in range(n):
                x = nums[i]
                for j in range(min(i + 1, k), -1, -1):
                    for l in range(1 << m):
                        if dp1[i][j][l]:
                            dp1[i + 1][j][l] = True
                            if j + 1 <= k:
                                dp1[i + 1][j + 1][l | x] = True
            return dp1

        dp1 = f(nums)
        dp2 = f(nums[::-1])

        ans = 0
        for i in range(k, n - k + 1):
            for j, x in enumerate(dp1[i][k]):
                if x:
                    for l, y in enumerate(dp2[n - i][k]):
                        if y:
                            t = j ^ l
                            if t > ans:
                                ans = t
        return ans
