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
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def countPairs(self, root: TreeNode, distance: int) -> int:
        ans = 0

        def dfs(root):
            nonlocal ans
            if not root:
                return []

            if not root.left and not root.right:
                return [0]

            ret = []

            # 处理左子树
            left = dfs(root.left)
            for i in range(len(left)):
                left[i] += 1  # 直接修改原数组
                if left[i] > distance:
                    continue
                ret.append(left[i])

            # 处理右子树
            right = dfs(root.right)
            for i in range(len(right)):
                right[i] += 1  # 直接修改原数组
                if right[i] > distance:
                    continue
                ret.append(right[i])

            # 统计跨子树的叶子节点对
            for l in left:
                for r in right:
                    if l + r <= distance:
                        ans += 1

            return ret

        dfs(root)
        return ans
