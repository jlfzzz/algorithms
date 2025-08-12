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
    def smallestMissingValueSubtree(
        self, parents: List[int], nums: List[int]
    ) -> List[int]:
        n = len(parents)
        ans = [1] * n
        if 1 not in nums:  # 不存在基因值为 1 的节点
            return ans

        # 建树
        g = [[] for _ in range(n)]
        for i in range(1, n):
            g[parents[i]].append(i)

        vis = set()

        def dfs(x: int) -> None:
            vis.add(nums[x])  # 标记基因值
            for son in g[x]:
                if nums[son] not in vis:
                    dfs(son)

        mex = 2  # 缺失的最小基因值
        node = nums.index(1)  # 出发点
        while node >= 0:
            dfs(node)
            while mex in vis:  # node 子树包含这个基因值
                mex += 1
            ans[node] = mex  # 缺失的最小基因值
            node = parents[node]  # 往上走
        return ans
