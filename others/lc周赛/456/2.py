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
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        n = len(words)

        def f(a: str, b: str) -> int:
            i = 0
            while i < len(a) and i < len(b) and a[i] == b[i]:
                i += 1
            return i

        if n == 1:
            return [0]

        neighbour = [f(words[i], words[i + 1]) for i in range(n - 1)]

        prefix = [0] * (n - 1)
        suffix = [0] * (n - 1)

        prefix[0] = neighbour[0]
        for i in range(1, n - 1):
            prefix[i] = max(prefix[i - 1], neighbour[i])

        suffix[-1] = neighbour[-1]
        for i in range(n - 3, -1, -1):
            suffix[i] = max(suffix[i + 1], neighbour[i])

        ans = []
        for i in range(n):
            if i == 0:
                ans.append(suffix[1] if n > 2 else 0)
            elif i == n - 1:
                ans.append(prefix[n - 3] if n > 2 else 0)
            else:
                leftRight = f(words[i - 1], words[i + 1])
                left = prefix[i - 2] if i >= 2 else 0
                right = suffix[i + 1] if i + 1 < n - 1 else 0
                ans.append(max(leftRight, left, right))

        return ans
