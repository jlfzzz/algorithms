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
    def strStr(self, haystack: str, needle: str) -> int:
        if not needle:
            return 0

        m, n = len(needle), len(haystack)

        # 构建 next 数组
        next = [0] * m
        j = 0
        for i in range(1, m):
            while j > 0 and needle[i] != needle[j]:
                j = next[j - 1]
            if needle[i] == needle[j]:
                j += 1
            next[i] = j

        # 匹配
        j = 0
        for i in range(n):
            while j > 0 and haystack[i] != needle[j]:
                j = next[j - 1]
            if haystack[i] == needle[j]:
                j += 1
            if j == m:
                return i - m + 1

        return -1


class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        return haystack.find(needle)
