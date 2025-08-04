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


# 带离散化
class FenwickTree:
    def __init__(self, size):
        self.tree = [0] * (size + 2)

    def update(self, i, val):
        while i < len(self.tree):
            self.tree[i] = max(self.tree[i], val)
            i += i & -i

    def query(self, i):
        res = 0
        while i > 0:
            res = max(res, self.tree[i])
            i -= i & -i
        return res


class Solution:
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:
        players = sorted(zip(ages, scores))
        all_scores = sorted(set(scores))
        score_id = {s: i + 1 for i, s in enumerate(all_scores)}  # 离散化

        ft = FenwickTree(len(all_scores))
        res = 0
        for age, score in players:
            idx = score_id[score]
            curr = ft.query(idx) + score
            ft.update(idx, curr)
            res = max(res, curr)
        return res


class FenwickTree:
    def __init__(self, n):
        self.tree = [0] * (n + 2)

    def update(self, i, val):
        while i < len(self.tree):
            self.tree[i] = max(self.tree[i], val)
            i += i & -i

    def query(self, i):
        ret = 0
        while i > 0:
            ret = max(ret, self.tree[i])
            i -= i & -i
        return ret


class Solution:
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:
        ft = FenwickTree(max(ages))
        arr = [(y, x) for x, y in zip(ages, scores)]
        arr.sort()
        ans = 0
        for score, age in arr:
            t = ft.query(age)
            ans = max(ans, t + score)
            ft.update(age, t + score)
        return ans


class Solution:
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:
        pairs = [[x, y] for x, y in zip(ages, scores)]
        pairs.sort()
        dp = [0] * len(scores)

        for i in range(len(pairs)):
            a, b = pairs[i]
            dp[i] = b
            for j in range(i):
                x, y = pairs[j]
                if b >= y:  # 当前球员得分 >= 之前球员得分，无冲突
                    dp[i] = max(dp[i], dp[j] + b)

        return max(dp)  # 返回所有dp值的最大值


class Solution:
    def bestTeamScore(self, scores: List[int], ages: List[int]) -> int:
        n = len(scores)
        pairs = list(zip(ages, scores))

        pairs.sort()
        dp = [0] * n
        ans = 0

        for i in range(n):
            dp[i] = pairs[i][1]
            for j in range(i):
                if pairs[j][1] <= pairs[i][1]:
                    dp[i] = max(dp[i], dp[j] + pairs[i][1])
            ans = max(ans, dp[i])

        return ans
