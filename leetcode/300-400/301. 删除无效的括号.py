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

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def removeInvalidParentheses(self, s: str) -> List[str]:
        min_remove = inf
        n = len(s)
        ans = set()

        def dfs(i: int, left: int, right: int, path: str) -> None:
            nonlocal min_remove
            if i == n:
                if left != right:
                    return
                m = len(path)
                if n - m < min_remove:
                    min_remove = n - m
                    ans.clear()
                    ans.add(path)
                elif n - m == min_remove:
                    ans.add(path)
                return

            c = s[i]
            if c == "(":
                dfs(i + 1, left + 1, right, path + "(")
                dfs(i + 1, left, right, path)
            elif c == ")":
                if right + 1 <= left:
                    dfs(i + 1, left, right + 1, path + ")")
                dfs(i + 1, left, right, path)
            else:
                dfs(i + 1, left, right, path + c)

        dfs(0, 0, 0, "")
        return list(ans)
