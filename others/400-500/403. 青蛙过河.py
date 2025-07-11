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
    def canCross(self, stones: List[int]) -> bool:
        if stones[1] != 1:
            return False
        n = len(stones)
        cnt = defaultdict()
        for i, x in enumerate(stones):
            cnt[x] = i

        @cache
        def dfs(i: int, prev: int) -> bool:
            if i == n - 1:
                return True

            diff = stones[i] - stones[prev]
            x = stones[i]
            if diff != 1 and x + diff - 1 in cnt and dfs(cnt[x + diff - 1], i):
                return True
            if x + diff in cnt and dfs(cnt[x + diff], i):
                return True
            if x + diff + 1 in cnt and dfs(cnt[x + diff + 1], i):
                return True
            return False

        return dfs(1, 0)
