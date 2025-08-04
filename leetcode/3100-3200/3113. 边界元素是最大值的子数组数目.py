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
    def numberOfSubarrays(self, nums: List[int]) -> int:
        st = []
        ans = 0
        cnt = defaultdict(int)
        for i, x in enumerate(nums):
            while st and x > st[-1]:
                y = st[-1]
                t = cnt[st[-1]]
                for _ in range(t):
                    st.pop()
                ans += (1 + t) * t // 2
                del cnt[y]
            st.append(x)
            cnt[x] += 1
        for x in cnt.values():
            ans += (1 + x) * x // 2
        return ans
