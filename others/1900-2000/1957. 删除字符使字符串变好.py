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
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def makeFancyString(self, s: str) -> str:
        ans = []
        cnt = 0
        for i, ch in enumerate(s):
            cnt += 1
            if cnt < 3:
                ans.append(ch)
            if i < len(s) - 1 and ch != s[i + 1]:
                cnt = 0  # 当前字母和下个字母不同，重置计数器
        return "".join(ans)
