from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [0] * n
        ors = []  # 按位或的值 + 对应子数组的右端点的最小值
        for i in range(n - 1, -1, -1):
            num = nums[i]
            ors.append([0, i])
            k = 0
            for p in ors:
                p[0] |= num
                if ors[k][0] == p[0]:
                    ors[k][1] = p[1]  # 合并相同值，下标取最小的
                else:
                    k += 1
                    ors[k] = p
            del ors[k + 1 :]
            # 本题只用到了 ors[0]，如果题目改成任意给定数值，可以在 ors 中查找
            ans[i] = ors[0][1] - i + 1
        return ans


class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        ans = [0] * len(nums)
        for i, x in enumerate(nums):
            ans[i] = 1
            for j in range(i - 1, -1, -1):
                if (nums[j] | x) == nums[j]:
                    break
                nums[j] |= x
                ans[j] = i - j + 1
        return ans


class Solution:
    def smallestSubarrays(self, nums: List[int]) -> List[int]:
        dis = [0] * 32
        n = len(nums)
        mx = 0
        ans = [-1] * n
        for i in range(n - 1, -1, -1):
            x = nums[i]
            mx |= x
            t = x
            for j in range(t.bit_length()):
                if t >> j & 1:
                    dis[j] = i
            if mx == 0:
                ans[i] = 1
            else:
                ans[i] = max(dis) - i + 1
        return ans
