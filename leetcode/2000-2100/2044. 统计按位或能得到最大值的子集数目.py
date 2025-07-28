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

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        def gen(A):
            ct = defaultdict(int)
            ct[0] = 1
            for a in A:
                for k, v in list(ct.items()):
                    ct[k | a] += v
            return ct

        M = reduce(or_, nums)
        n = len(nums)
        A, B = nums[: n // 2], nums[n // 2 :]
        res = 0
        ct1, ct2 = gen(A), gen(B)
        for a in ct1:
            for b in ct2:
                if a | b == M:
                    res += ct1[a] * ct2[b]
        return res
