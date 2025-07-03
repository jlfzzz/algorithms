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
    def kthCharacter(self, k: int, operations: List[int]) -> str:
        n = len(operations)
        cnt = 0
        for i in range(n - 1, -1, -1):
            m = 1 << i
            if k > m:
                cnt += operations[i]
                k -= m
        return ascii_lowercase[cnt % 26]
