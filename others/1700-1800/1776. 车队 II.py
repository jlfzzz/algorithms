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

        st = []
        ans = [-1.0] * n
        for i in range(n - 1, -1, -1):
            pos, speed = cars[i][0], cars[i][1]

            # 如果最后一个的速度更大，直接删除
            # 因为只看最后一个，我们永远追不上
            # 把它删了，就能继续去看栈里面的速度更小的
            # 对于栈里面的速度更小的，如果当前能追上，那么这个已经删除的更快的肯定也能追上
            # 所以这个更快的对当前来说，没用处了
            while st and speed <= cars[st[-1]][1]:
                st.pop()

            while st:
                j = st[-1]
                pos2, speed2 = cars[j][0], cars[j][1]
                # 追上栈最后一个的所需时间
                t = (pos2 - pos) / (speed - speed2)

                if ans[j] == -1.0 or t <= ans[j]: # 如果追上栈最后一个的时间小于ans[j]，能在最后一个追上它的下一个之前追上，更新答案
                    ans[i] = t
                    break
                
                # 连最后一个都追不上了，删除。去看倒数第二个（如果有），这个倒数第二个会被刚刚的这个最后一个追上，去查看倒数第二个的状态
                st.pop()

            st.append(i)
        return ans


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
