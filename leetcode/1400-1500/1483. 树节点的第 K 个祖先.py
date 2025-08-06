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


class TreeAncestor:

    def __init__(self, n: int, parent: List[int]):
        m = n.bit_length()
        pa = [[-1] * m for _ in range(n)]
        for i, x in enumerate(parent):
            pa[i][0] = x

        for i in range(1, m):
            for j in range(n):
                if pa[j][i - 1] != -1:  # 检查前一个祖先是否存在
                    pa[j][i] = pa[pa[j][i - 1]][i - 1]
        self.pa = pa
        self.m = m

    def getKthAncestor(self, node: int, k: int) -> int:
        for i in range(self.m - 1, -1, -1):
            if k >= (1 << i):
                if self.pa[node][i] == -1:  # 添加安全检查
                    return -1
                node = self.pa[node][i]
                k -= 1 << i
        return node


# Your TreeAncestor object will be instantiated and called as such:
# obj = TreeAncestor(n, parent)
# param_1 = obj.getKthAncestor(node,k)


class TreeAncestor:

    def __init__(self, n: int, parent: List[int]):
        m = n.bit_length() - 1
        pa = [[p] + [-1] * m for p in parent]
        for i in range(m):
            for x in range(n):
                p = pa[x][i]
                if p != -1:
                    pa[x][i + 1] = pa[p][i]
        self.pa = pa

    def getKthAncestor(self, node: int, k: int) -> int:
        for i in range(k.bit_length()):
            if k >> i & 1:
                node = self.pa[node][i]
                if node < 0:
                    break
        return node


# Your TreeAncestor object will be instantiated and called as such:
# obj = TreeAncestor(n, parent)
# param_1 = obj.getKthAncestor(node,k)
