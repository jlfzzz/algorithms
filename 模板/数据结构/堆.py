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
INF = float('inf')
MOD = int(1e9 + 7)


# 懒删除堆，lc3607 并查集+懒删除堆
# 额外一个 数组 维护堆中的每个元素的状态
# pop的时候如果状态不符合要求就继续pop
class UnionFind:
    def __init__(self, n):
        self.fa = list(range(n))
        self.heaps = [[] for _ in range(n)]
        self.offline = [False] * n
        for i in range(1, n):
            self.heaps[i].append(i)  # 从1开始初始化堆

    def find(self, x):
        if self.fa[x] != x:
            self.fa[x] = self.find(self.fa[x])
        return self.fa[x]

    def merge(self, x, y):
        a, b = self.find(x), self.find(y)
        if a == b:
            return
        if len(self.heaps[a]) < len(self.heaps[b]):
            a, b = b, a
        self.fa[b] = a
        while self.heaps[b]:
            heappush(self.heaps[a], heappop(self.heaps[b]))

    def pop_min(self, x):
        fa = self.find(x)
        while self.heaps[fa]:
            t = heappop(self.heaps[fa])
            if not self.offline[t]:
                heappush(self.heaps[fa], t)  # 推回去（只是找最小，不删）
                return t
        return -1

    def remove(self, x):
        self.offline[x] = True


class Solution:
    def processQueries(
        self, c: int, connections: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        uf = UnionFind(c + 1)  # c从1到c，预留0位置
        for a, b in connections:
            uf.merge(a, b)

        ans = []
        for query in queries:
            if query[0] == 1:
                _, b = query
                if not uf.offline[b]:
                    ans.append(b)
                else:
                    res = uf.pop_min(b)
                    ans.append(res)
            elif query[0] == 2:
                _, b = query
                uf.remove(b)

        return ans


# 反悔堆
# lc lcp30 
# 贪心，先把之前的所有特殊元素加入堆
# 超过边界了再去堆顶pop最优解
class Solution:
    def magicTower(self, nums: List[int]) -> int:
        if sum(nums) + 1 <= 0:
            return -1

        curr = 1
        ans = 0
        h = []  # 小根堆存负数（最大负数在堆顶）

        for x in nums:
            curr += x
            if x < 0:
                heappush(h, x)
            if curr <= 0:
                # 当前血量已经不能活了，需要反悔之前最大的负数
                t = heappop(h)
                curr -= t  # 把它推迟（现在不吃了）
                ans += 1
        return ans
