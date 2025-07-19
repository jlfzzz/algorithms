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
INF = float("inf")
MOD = int(1e9 + 7)


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
        n = len(nums)
        stk = list()
        tree = [None] * n

        for i in range(n):
            tree[i] = TreeNode(nums[i])
            while stk and nums[i] > nums[stk[-1]]:
                tree[i].left = tree[stk[-1]]
                stk.pop()
            if stk:
                tree[stk[-1]].right = tree[i]
            stk.append(i)

        return tree[stk[0]]


class Solution:
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
        n = len(nums)
        left, right = [-1] * n, [-1] * n
        st = []
        trees = [None] * n

        # 使用单调栈找到每个元素左边和右边第一个比它大的元素
        for i in range(n):
            x = nums[i]
            trees[i] = TreeNode(x)

            # 找右边第一个比当前元素大的
            while st and x > nums[st[-1]]:
                right[st[-1]] = i
                st.pop()

            # 找左边第一个比当前元素大的
            if st:
                left[i] = st[-1]
            st.append(i)

        # 构建树的父子关系
        ret = None
        for i in range(n):
            l, r = left[i], right[i]

            # 如果左右都没有比它大的元素，说明它是根节点
            if l == -1 and r == -1:
                ret = trees[i]
            else:
                # 选择距离更近的作为父节点
                if l == -1:  # 左边没有更大的，右边的作为父节点
                    trees[r].left = trees[i]
                elif r == -1:  # 右边没有更大的，左边的作为父节点
                    trees[l].right = trees[i]
                else:  # 左右都有更大的，选择值较小的（距离更近的）作为父节点
                    if nums[l] < nums[r]:
                        trees[l].right = trees[i]
                    else:
                        trees[r].left = trees[i]

        return ret


class Solution:
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
        if not nums:
            return None
        i, val = max(enumerate(nums), key=lambda x: x[1])
        node = TreeNode(
            val,
            self.constructMaximumBinaryTree(nums[:i]),
            self.constructMaximumBinaryTree(nums[i + 1 :]),
        )
        return node
