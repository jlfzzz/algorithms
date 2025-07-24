# Definition for a binary tree node.
from math import inf
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def kthLargestPerfectSubtree(self, root: Optional[TreeNode], k: int) -> int:
        ans = []

        def dfs(node: Optional[TreeNode]) -> int:
            if not node:
                return 0

            left = dfs(node.left)
            right = dfs(node.right)
            if left == -inf or right == -inf:
                return -inf
            if left != right:
                return -inf
            ans.append(left + right + 1)
            return left + right + 1

        dfs(root)
        ans.sort()
        return -1 if len(ans) < k else ans[len(ans) - k]
