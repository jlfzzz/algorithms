from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
INF = int(1e9)

pow2 = [1] * 100_000
for i in range(1, 100_000):
    pow2[i] = pow2[i - 1] * 2 % MOD


class Solution:
    def numSubseq(self, nums: List[int], target: int) -> int:
        nums.sort()
        n = len(nums)
        ans = 0
        left = 0
        right = n - 1

        while left <= right:
            if nums[left] + nums[right] > target:
                right -= 1
            else:
                ans = (ans + pow2[right - left]) % MOD
                left += 1

        return ans
