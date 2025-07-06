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
    def numberOfSubstrings(self, s: str, k: int) -> int:
        n = len(s)
        cnt = [0] * 26
        left, ans = 0, 0
        for right, c in enumerate(s):
            cnt[ord(c) - ord("a")] += 1
            while cnt[ord(c) - ord("a")] == k:
                ans += n - right
                cnt[ord(s[left]) - ord("a")] -= 1
                left += 1
        return ans
