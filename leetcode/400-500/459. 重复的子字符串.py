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
    def repeatedSubstringPattern(self, s: str) -> bool:
        n = len(s)
        for i in range(1, n // 2 + 1):
            if n % i == 0:
                if all(s[j] == s[j - i] for j in range(i, n)):
                    return True
        return False


class Solution:
    def repeatedSubstringPattern(self, s: str) -> bool:
        return (s + s).find(s, 1) != len(s)


class Solution:
    def repeatedSubstringPattern(self, s: str) -> bool:
        n = len(s)
        next = [0] * n
        leng = 0
        i = 1
        while i < n:
            while leng > 0 and s[i] != s[leng]:
                leng = next[leng - 1]
            if s[i] == s[leng]:
                leng += 1
            next[i] = leng
            i += 1

        pattern_len = n - next[n - 1]

        # 如果n能被pattern_len整除，且pattern_len < n，则存在重复模式
        return pattern_len < n and n % pattern_len == 0
