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
    def processStr(self, s: str) -> str:
        res = ""
        for c in s:
            if c == "*":
                if len(res) > 0:
                    res = res[: len(res) - 1]
            elif c == "#":
                res = res + res
            elif c == "%":
                res = res[::-1]
            else:
                res = res + c
        return res
