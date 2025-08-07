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
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        ans = []
        st = set()
        cnt = Counter(s)
        for c in s:
            cnt[c] -= 1
            if c in st:
                continue
            while ans and c < ans[-1] and cnt[ans[-1]]:
                st.remove(ans.pop())
            ans.append(c)
            st.add(c)
        return "".join(ans)
