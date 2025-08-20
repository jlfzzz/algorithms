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
from sortedcontainers import *


DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)
class Solution:
    def zeroFilledSubarray(self, nums: List[int]) -> int:
        ans = cnt0 = 0
        for x in nums:
            if x:
                cnt0 = 0
            else:
                cnt0 += 1  # 右端点为 i 的全 0 子数组比右端点为 i-1 的全 0 子数组多一个
                ans += cnt0
        return ans
