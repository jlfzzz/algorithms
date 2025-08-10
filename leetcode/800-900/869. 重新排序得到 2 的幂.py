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


pow_two_sorted_str_set = {"".join(sorted(str(1 << i))) for i in range(30)}


class Solution:
    def reorderedPowerOf2(self, n: int) -> bool:
        s = "".join(sorted(str(n)))
        return s in pow_two_sorted_str_set


class Solution:
    def reorderedPowerOf2(self, n: int) -> bool:
        s = str(n)
        cnt = Counter(s)
        ans = False

        def dfs(curr, i):
            nonlocal ans
            if i == len(s):
                if curr > 0 and (curr & -curr) == curr:
                    ans = True
                return
            if ans:
                return
            for k, v in cnt.items():
                if v > 0:
                    cnt[k] -= 1
                    dfs(curr * 10 + int(k), i + 1)
                    cnt[k] += 1

        for k, v in cnt.items():
            if k == "0":  # 不能有前导零
                continue
            cnt[k] -= 1
            dfs(int(k), 1)
            cnt[k] += 1

        return ans
