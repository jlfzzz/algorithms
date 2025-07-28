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
INF = float("inf")
MOD = int(1e9 + 7)


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxSumBST(self, root: Optional[TreeNode]) -> int:
        ans = 0

        def dfs(node: Optional[TreeNode]):
            if not node:
                return (inf, -inf, 0)

            t = node.val

            l_mn, l_mx, l = dfs(node.left)
            r_mn, r_mx, r = dfs(node.right)

            if l_mx >= t or r_mn <= t:
                return (-inf, inf, 0)
            nonlocal ans
            ans = Max(ans, l + r + t)

            return (min(l_mn, r_mn, t), max(l_mx, r_mx, t), l + r + t)

        dfs(root)
        return ans
