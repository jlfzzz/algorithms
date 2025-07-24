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

#树哈希
class Solution:
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        # 匹配遍历结果
        # 不过要为遍历结果加上一些标识 以保证是树和树之间匹配，而不是节点间匹配
        # 一棵树的遍历结果为 (root.val(root.left)(root.right))
        # 其中空节点应当返回 ()，以标识树的结束
        # 这样的话，任何一种遍历结果都是可行的

        def dfs(node: Optional[TreeNode]) -> str:
            if node is None:
                return "()"

            return f"({node.val}({dfs(node.left)})({dfs(node.right)}))"

        return dfs(subRoot) in dfs(root)


class Solution:
    def isSubtree(self, root: Optional[TreeNode], subRoot: Optional[TreeNode]) -> bool:
        path1 = []
        path2 = []
        # 确保两个树完全一样
        lNull, rNull = -1000000, -1000001

        def dfs(node, path):
            path.append(node.val)
            if node.left:
                dfs(node.left, path)
            else:
                path.append(lNull)
            if node.right:
                dfs(node.right, path)
            else:
                path.append(rNull)

        dfs(root, path1)
        dfs(subRoot, path2)
        n = len(path1)
        m = len(path2)
        nxt = [0] * m
        i = 1
        length = 0
        while i < m:
            while length > 0 and path2[length] != path2[i]:
                length = nxt[length - 1]
            if path2[length] == path2[i]:
                length += 1
            nxt[i] = length
            i += 1
        i, j = 0, 0
        while i < n:
            while j > 0 and path1[i] != path2[j]:
                j = nxt[j - 1]
            if path1[i] == path2[j]:
                j += 1
            if j == m:
                return True
            i += 1
        return False


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
