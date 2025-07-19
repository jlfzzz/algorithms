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
    def insertIntoMaxTree(
        self, root: Optional[TreeNode], val: int
    ) -> Optional[TreeNode]:
        parent, cur = None, root
        while cur:
            if val > cur.val:
                if not parent:
                    return TreeNode(val, root, None)
                node = TreeNode(val, cur, None)
                parent.right = node
                return root
            else:
                parent = cur
                cur = cur.right

        parent.right = TreeNode(val)
        return root
