from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def kthCharacter(self, k: int) -> str:
        s = "a"
        while len(s) < k:
            t = ""
            for c in s:
                t += str(chr((ord(c) - ord("a") + 1) % 26 + ord("a")))
            s += t
        return s[k - 1]
