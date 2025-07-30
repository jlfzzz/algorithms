from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        n = len(words)

        ans = []
        i = 0
        while i < n:
            curr = len(words[i])
            j = i + 1
            while j < n:
                t = len(words[j])
                if curr + 1 + t > maxWidth:
                    break
                curr += 1 + t
                j += 1

            cnt = j - i
            words_len = 0
            for k in range(i, j):
                words_len += len(words[k])
            spaces = maxWidth - words_len

            if cnt == 1:
                s = words[i] + " " * (maxWidth - len(words[i]))
                ans.append(s)
                i = j
                continue

            if j == n:
                s = ""
                for k in range(i, j):
                    s += words[k]
                    if k != j - 1:
                        s += " "
                s += " " * (maxWidth - len(s))
                ans.append(s)
                i = j
                break

            mn = spaces // (cnt - 1)
            extra = spaces % (cnt - 1)

            s = ""
            for k in range(i, j):
                s += words[k]
                if k != j - 1:
                    s += " " * mn
                    if extra:
                        s += " "
                        extra -= 1
            ans.append(s)
            i = j
        return ans
