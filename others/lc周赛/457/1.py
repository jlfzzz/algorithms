from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
import re
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def validateCoupons(
        self, code: List[str], businessLine: List[str], isActive: List[bool]
    ) -> List[str]:
        n = len(code)
        ans1, ans2, ans3, ans4 = [], [], [], []
        for i in range(n):
            c, b, isA = code[i], businessLine[i], isActive[i]
            if isA and len(c) > 0 and bool(re.fullmatch(r"[a-zA-Z0-9_]+", c)):
                if b == "electronics©leetcode":
                    ans1.append(c)
                elif b == "grocery":
                    ans2.append(c)
                elif b == "pharmacy":
                    ans3.append(c)
                elif b == "restaurant":
                    ans4.append(c)
        ans1.sort()
        ans2.sort()
        ans3.sort()
        ans4.sort()
        ans = ans1 + ans2 + ans3 + ans4
        return ans
