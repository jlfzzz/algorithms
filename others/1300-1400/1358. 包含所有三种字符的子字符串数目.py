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
    def numberOfSubstrings(self, s: str) -> int:
        n = len(s)
        ans = 0
        left = 0
        cnt = [0] * 3
        for right, c in enumerate(s):
            cnt[ord(c) - ord("a")] += 1
            while cnt[0] and cnt[1] and cnt[2]:
                ans += n - right
                cnt[ord(s[left]) - ord("a")] -= 1
                left += 1
        return ans
