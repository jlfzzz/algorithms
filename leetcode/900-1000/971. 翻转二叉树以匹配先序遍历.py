from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def flipMatchVoyage(self, root: Optional[TreeNode], voyage: List[int]) -> List[int]:
        ans = []
        can = True

        def dfs(node: Optional[TreeNode]) -> None:
            nonlocal i
            nonlocal can
            if not can:
                return

            if node.val != voyage[i]:
                can = False
                return
            i += 1
            if node.left and node.right:
                if node.left.val == voyage[i]:
                    dfs(node.left)
                    dfs(node.right)
                else:
                    ans.append(node.val)
                    dfs(node.right)
                    dfs(node.left)
                return
            if node.left:
                dfs(node.left)
            if node.right:
                dfs(node.right)

        i = 0
        dfs(root)
        return ans if can else [-1]
