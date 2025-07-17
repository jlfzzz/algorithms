from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def validSubstringCount(self, word1: str, word2: str) -> int:
        cnt = Counter(word2)
        window = defaultdict(int)
        matches = 0
        m = len(cnt)
        n = len(word1)
        left = 0
        ans = 0
        for right, c in enumerate(word1):
            if c in cnt:
                window[c] += 1
                if window[c] == cnt[c]:
                    matches += 1

            while matches == m:
                ans += n - right
                if word1[left] in cnt and window[word1[left]] == cnt[word1[left]]:
                    matches -= 1
                window[word1[left]] -= 1
                left += 1
        return ans
