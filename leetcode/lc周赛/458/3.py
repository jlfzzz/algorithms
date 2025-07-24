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
MOD = int(1e9 + 7)


class Solution:
    def processStr(self, s: str, k: int) -> str:
        n = len(s)
        curr_len = [0] * (n + 1)
        for i in range(1, n + 1):
            c = s[i - 1]
            if c == "*":
                if curr_len[i - 1] > 0:
                    curr_len[i] = curr_len[i - 1] - 1
            elif c == "#":
                curr_len[i] = curr_len[i - 1] * 2
            elif c == "%":
                curr_len[i] = curr_len[i - 1]
            else:
                curr_len[i] = curr_len[i - 1] + 1
        if curr_len[-1] <= k:
            return "."

        for i in range(n, 0, -1):
            c = s[i - 1]
            curr = curr_len[i]

            if c == "#":
                if k >= curr // 2:
                    k -= curr // 2
            elif c == "%":
                k = curr - k - 1
            elif c == "*":
                # if k + 1 == curr:
                #     k += 1
                continue
            else:
                if k + 1 == curr:
                    return c
        return "."
