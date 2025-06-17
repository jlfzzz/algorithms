# Definition for a binary tree node.
from collections import defaultdict
from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        ans = [[] for _ in range(2005)]

        def dfs(node: Optional[TreeNode], x, y):
            if not node:
                return
            ans[y + 1002].append((x, node.val))
            dfs(node.left, x + 1, y - 1)
            dfs(node.right, x + 1, y + 1)

        dfs(root, 0, 0)
        real_ans = []
        for i in range(2005):
            if ans[i]:  # 如果当前列有值
                col = sorted(ans[i])  # 按 x、val 排序
                real_ans.append([val for x, val in col])
        return real_ans


class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        groups = defaultdict(list)

        def dfs(node: Optional[TreeNode], row: int, col: int):
            if node is None:
                return
            groups[col].append((row, node.val))  # col 相同的分到同一组
            dfs(node.left, row + 1, col - 1)
            dfs(node.right, row + 1, col + 1)

        dfs(root, 0, 0)

        ans = []
        for _, g in sorted(groups.items()):
            g.sort()  # 按照 row 排序，row 相同按照 val 排序
            ans.append([val for _, val in g])
        return ans
