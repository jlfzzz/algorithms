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
    def isValid(self, word: str) -> bool:
        if len(word) < 3:
            return False
        f = [False] * 2
        for c in word:
            if c.isalpha():
                f[c.lower() in "aeiou"] = True
            elif not c.isdigit():
                return False
        return all(f)
