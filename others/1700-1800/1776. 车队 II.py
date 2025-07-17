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


class Solution:
    def getCollisionTimes(self, cars: List[List[int]]) -> List[float]:

        n = len(cars)
        ans = [-1.0] * n
        stack = []  # 单调栈，栈底：车速更慢，且初始位置更靠右

        for i in range(n - 1, -1, -1):  # 从右往左遍历
            pos, speed = cars[i]

            # 弹出栈顶速度更快的车辆，直到栈顶车的速度小于当前车辆
            while stack and speed <= cars[stack[-1]][1]:
                stack.pop()

            # 从栈顶往栈底依次检查当前车是否能及时追上目标车辆
            while stack:
                j = stack[-1]
                time = (cars[j][0] - pos) / (speed - cars[j][1])
                if ans[j] < 0 or time <= ans[j]:  # 若及时追上了，此即为解
                    ans[i] = time
                    break
                stack.pop()  # 否则弹出栈顶这辆已经检查过的车，准备看下一辆

            stack.append(i)  # 此时当前车辆的速度一定大于栈顶的车辆，需入栈

        return ans
