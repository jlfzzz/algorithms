from bisect import bisect_left
from functools import cache
from math import inf
from typing import List
from collections import *


class Solution:
    def minOperations(self, target: List[int], arr: List[int]) -> int:
        mp = defaultdict(int)
        for i, x in enumerate(target):
            mp[x] = i

        ans = []
        for x in arr:
            if x in mp:
                idx = mp[x]
                it = bisect_left(ans, idx)
                if it < len(ans):
                    ans[it] = idx
                else:
                    ans.append(idx)
        return len(target) - len(ans)


class Solution:
    def minOperations(self, target: List[int], arr: List[int]) -> int:
        n = len(target)
        m = len(arr)

        @cache
        def dfs(i: int, j: int, ops: int) -> int:
            if i == n:
                return ops
            if j == m:
                return ops + n - i

            res = dfs(i + 1, j + 1, ops) if target[i] == arr[j] else inf
            res = min(res, dfs(i + 1, j, ops + 1), dfs(i, j + 1, ops))
            return res

        return dfs(0, 0, 0)


class Solution:
    def minOperations(self, target: List[int], arr: List[int]) -> int:
        n = len(target)
        m = len(arr)

        memo = [[-1] * m for _ in range(n)]

        def dfs(i: int, j: int) -> int:
            if i == n:
                return 0
            if j == m:
                return n - i

            res = inf
            if target[i] == arr[j]:
                res = dfs(i + 1, j + 1)
            res = min(res, 1 + dfs(i + 1, j), dfs(i, j + 1))
            return res

        return dfs(0, 0)
