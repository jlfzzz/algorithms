# Definition for a binary tree node.
from typing import List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def averageOfSubtree(self, root: TreeNode) -> List:
        ans = 0

        def dfs(node: TreeNode) -> int:
            if not node:
                return [0, 0]

            left = dfs(node.left)
            right = dfs(node.right)
            nonlocal ans
            if (left[0] + right[0] + node.val) // (left[1] + right[1] + 1) == node.val:
                ans += 1
            return [left[0] + right[0] + node.val, left[1] + right[1] + 1]

        dfs(root)
        return ans
