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
    def rotateString(self, s: str, goal: str) -> bool:
        if len(s) != len(goal):
            return False
        s = s + s
        n = len(s)
        m = len(goal)
        next = [0] * m

        length = 0
        i = 1
        while i < m:
            while length > 0 and goal[length] != goal[i]:
                length = next[length - 1]
            if s[length] == goal[i]:
                length += 1
            next[i] = length
            i += 1

        i = 0
        j = 0
        while i < n:
            while j > 0 and goal[j] != s[i]:
                j = next[j - 1]
            if goal[j] == s[i]:
                j += 1
            if j == m:
                return True
            i += 1
        return False
