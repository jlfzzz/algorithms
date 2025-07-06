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
    def minMoves(self, sx: int, sy: int, x: int, y: int) -> int:
        ans = 0
        while x != sx or y != sy:
            if x < sx or y < sy:
                return -1
            if x == y:
                if sy > 0:
                    x = 0
                else:
                    y = 0
                ans += 1
                continue
            # 保证 x > y
            if x < y:
                x, y = y, x
                sx, sy = sy, sx
            if x > y * 2:
                if x % 2 > 0:
                    return -1
                x //= 2
            else:
                x -= y
            ans += 1
        return ans
