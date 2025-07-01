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


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        ans = 0

        def dfs(node: Optional[TreeNode]) -> List:
            if not node:
                return [-1, -1]
            ll, lr = dfs(node.left)
            rl, rr = dfs(node.right)
            nonlocal ans
            ans = max(ans, 1 + lr, 1 + rl)
            return [lr + 1, rl + 1]

        dfs(root)
        return ans
