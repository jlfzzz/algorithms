# Definition for a binary tree node.
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def findTilt(self, root: Optional[TreeNode]) -> int:

        ans = 0

        def dfs(root: Optional[TreeNode]) -> int:
            if not root:
                return 0
            nonlocal ans
            left = dfs(root.left)
            right = dfs(root.right)
            ans += abs(left - right)
            return left + right + root.val

        dfs(root)
        return ans
