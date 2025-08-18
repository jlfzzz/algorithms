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
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        B = int(sqrt(n))
        d = defaultdict(list)

        def inv(x):
            return pow(x, MOD - 2, MOD)

        for l, r, k, v in queries:
            if (r - l + 1) // k <= B:
                for i in range(l, r + 1, k):
                    nums[i] = (nums[i] * v) % MOD
            else:
                offset = l % k
                left, right = l // k, (r - offset) // k
                key = (offset, k)
                if key not in d:
                    d[key] = [1 for _ in range(n // k + 3)]
                d[key][left] *= v
                d[key][left] %= MOD
                d[key][right + 1] *= inv(v)
                d[key][right + 1] %= MOD
        for (offset, k), v in d.items():
            for i in range(1, len(v)):
                v[i] = v[i - 1] * v[i] % MOD

            for i in range(len(v)):
                j = offset + i * k
                if j >= 0 and j < n:
                    nums[j] = nums[j] * v[i] % MOD
        ans = 0
        for x in nums:
            ans ^= x
        return ans
