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
MOD = int(1337)


class Solution:
    def superPow(self, a: int, b: List[int]) -> int:
        MOD = 1337
        ans = 1
        for x in b:
            ans = pow(ans, 10, MOD) * pow(a, x, MOD)
        return ans


class Solution:
    def superPow(self, a: int, b: List[int]) -> int:
        MOD = 1337
        ans = 1
        for e in reversed(b):
            ans = ans * pow(a, e, MOD) % MOD
            a = pow(a, 10, MOD)
        return ans


class Solution:
    def superPow(self, a: int, b: List[int]) -> int:
        ans = 1
        base = a

        def f(nums: List[int]) -> List[int]:
            ret = []

            prev = 0
            for i, x in enumerate(nums):
                curr = x + prev * 10
                ret.append(curr // 2)
                prev = curr % 2

            i = 0
            while i < len(ret) and ret[i] == 0:
                i += 1
            return ret[i:]

        while True:

            if len(b) == 1 and b[0] == 1:
                ans = (ans * base) % MOD
                break

            if b[-1] & 1:
                ans = (ans * base) % MOD
            base = (base * base) % MOD
            b = f(b)
        return ans
