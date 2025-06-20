# Definition for a binary tree node.
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        ans = 0

        def dfs(root: Optional[TreeNode]) -> list:
            x = root.val
            nonlocal ans
            mn, mx = x, x
            if root.left:
                l = dfs(root.left)
                mn = min(mn, l[0])
                mx = max(mx, l[1])
                ans = max(ans, abs(x - l[0]), abs(x - l[1]))
            if root.right:
                r = dfs(root.right)
                mn = min(mn, r[0])
                mx = max(mx, r[1])
                ans = max(ans, abs(x - r[0]), abs(x - r[1]))
            return [mn, mx]

        dfs(root)
        return ans
