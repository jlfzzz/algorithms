from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        ans = mx = cnt = 0
        for x in nums:
            if x > mx:
                # 发现新的 mx，重新统计所有内容
                mx = x
                ans = cnt = 1
            elif x == mx:
                cnt += 1
                if cnt > ans:  # 手写 max 更快
                    ans = cnt
            else:
                cnt = 0  # 连续 mx 断开了，重新统计
        return ans


class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        mx = max(nums)
        ans = 1

        left = 0
        window = False
        for right, x in enumerate(nums):
            if x & mx != mx:
                left = right + 1
                window = False
            else:
                if x == mx:
                    window = True
                if window:
                    ans = max(ans, right - left + 1)
        return ans
