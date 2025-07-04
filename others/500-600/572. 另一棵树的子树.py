from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    # 代码逻辑同 104. 二叉树的最大深度
    def getHeight(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        left_h = self.getHeight(root.left)
        right_h = self.getHeight(root.right)
        return max(left_h, right_h) + 1

    # 100. 相同的树
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        if p is None or q is None:
            return p is q  # 必须都是 None
        return (
            p.val == q.val
            and self.isSameTree(p.left, q.left)
            and self.isSameTree(p.right, q.right)
        )

    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        hs = self.getHeight(subRoot)

        # 返回 node 的高度，以及是否找到了 subRoot
        def dfs(node: Optional[TreeNode]) -> Tuple[int, bool]:
            if node is None:
                return 0, False
            left_h, left_found = dfs(node.left)
            right_h, right_found = dfs(node.right)
            if left_found or right_found:
                return 0, True
            node_h = max(left_h, right_h) + 1
            return node_h, node_h == hs and self.isSameTree(node, subRoot)

        return dfs(root)[1]


class Solution:
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        def dfs1(node):
            if not node:
                return False
            res = False

            def dfs2(node, node2):
                if not node:
                    return True if not node2 else False
                if not node2:
                    return True if not node else False
                if node.val != node2.val:
                    return False
                return dfs2(node.left, node2.left) and dfs2(node.right, node2.right)

            if node.val == subRoot.val:
                res |= dfs2(node, subRoot)
            return res or dfs1(node.left) or dfs1(node.right)

        return dfs1(root)
