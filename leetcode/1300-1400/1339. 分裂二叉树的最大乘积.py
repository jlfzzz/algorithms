# Definition for a binary tree node.
from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        ans = -1
        MOD = int(1e9 + 7)
        s = 0

        def dfs1(node: Optional[TreeNode]):
            if not node:
                return
            nonlocal s
            s += node.val
            dfs1(node.left)
            dfs1(node.right)

        def dfs(node: Optional[TreeNode]):
            if not node:
                return 0
            left = dfs(node.left)
            right = dfs(node.right)
            nonlocal ans
            ans = max(ans, (s - right) * right, (s - left) * left)
            return left + right + node.val

        dfs(root)
        return ans % MOD
