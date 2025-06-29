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
INF = int(1e9)


class Solution:
    def partitionString(self, s: str) -> List[str]:
        appear = defaultdict(str)
        cnt = []
        path = ""
        for right, c in enumerate(s):
            path += c
            if path not in appear:
                cnt.append(path)
                appear[path] = 1
                path = ""
        ans = list(cnt)
        return ans
