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
    def minDeletion(self, s: str, k: int) -> int:
        cnt = sorted(Counter(s).values())
        return sum(cnt[:-k])  # 保留出现次数最大的 k 个字母


class Solution:
    def minDeletion(self, s: str, k: int) -> int:
        cnt = [0] * 26
        for c in s:
            cnt[ord(c) - ord("a")] += 1
        cnt.sort()
        i = 0
        while i < 26 and cnt[i] == 0:
            i += 1
        ans = 0
        while 26 - i > k:
            ans += cnt[i]
            i += 1
        return ans
