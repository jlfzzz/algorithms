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
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        ans = 0
        while tx > sx or ty > sy:
            if tx < sx or ty < sy:
                return -1

            if tx == ty:
                if sx == 0:
                    tx = 0
                elif sy == 0:
                    ty = 0
                else:
                    return -1
                ans += 1
                continue

            if tx > ty:
                tx, ty = ty, tx
                sx, sy = sy, sx

            if ty > 2 * tx:
                if ty % 2:
                    return -1

                ty //= 2
            else:
                ty -= tx
            ans += 1
        if tx == sx and ty == sy:
            return ans
        return -1


class Solution:
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        ans = 0
        while sx != tx or sy != ty:
            if tx < sx or ty < sy:
                return -1
            if tx == ty:
                if sx == 0:
                    tx = 0
                else:
                    ty = 0
                ans += 1
                continue
            if tx < ty:
                tx, ty = ty, tx
                sx, sy = sy, sx
            if tx > 2 * ty:
                if tx % 2:
                    return -1
                tx //= 2
            else:
                tx -= ty
            print("+1")
            ans += 1
        return ans


s = Solution()
s.minMoves(1, 2, 5, 4)


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
