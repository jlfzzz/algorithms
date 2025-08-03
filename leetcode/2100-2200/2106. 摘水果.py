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
    def maxTotalFruits(self, fruits: List[List[int]], startPos: int, k: int) -> int:
        # 找到最右边的位置
        if not fruits:
            return 0

        right_most = fruits[-1][0]
        left_most = fruits[0][0]

        # 扩展范围以包含可能的起始位置
        min_pos = min(left_most, startPos - k)
        max_pos = max(right_most, startPos + k)

        # 创建位置到水果数量的映射数组
        nums = [0] * (max_pos - min_pos + 1)
        for pos, count in fruits:
            nums[pos - min_pos] = count

        # 调整startPos到数组索引
        start_idx = startPos - min_pos

        ans = 0

        # 情况1：先往左走，再往右走
        # 初始化：只往左走k步
        left_bound = max(0, start_idx - k)
        window = sum(nums[left_bound : start_idx + 1])
        ans = max(ans, window)

        # 滑动窗口：逐步减少左边范围，增加右边范围
        right_steps = 1
        while left_bound + 2 <= start_idx and start_idx + right_steps < len(nums):
            # 往右多走一步
            window += nums[start_idx + right_steps]
            right_steps += 1

            # 左边减少两步的范围
            window -= nums[left_bound]
            left_bound += 1
            # if left_bound <= start_idx:
            window -= nums[left_bound]
            left_bound += 1

            ans = max(ans, window)

        # 情况2：先往右走，再往左走
        # 初始化：只往右走k步
        right_bound = min(len(nums) - 1, start_idx + k)
        window = sum(nums[start_idx : right_bound + 1])
        ans = max(ans, window)

        # 滑动窗口：逐步减少右边范围，增加左边范围
        left_steps = 1
        while right_bound - 2 >= start_idx and start_idx - left_steps >= 0:
            # 往左多走一步
            window += nums[start_idx - left_steps]
            left_steps += 1

            # 右边减少两步的范围
            window -= nums[right_bound]
            right_bound -= 1
            # if right_bound >= start_idx:
            window -= nums[right_bound]
            right_bound -= 1

            ans = max(ans, window)

        return ans
