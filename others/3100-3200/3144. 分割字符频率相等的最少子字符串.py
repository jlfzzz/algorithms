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
    def minimumSubstringsInPartition(self, s: str) -> int:
        n = len(s)
        f = [0] + [inf] * n
        for i in range(n):
            cnt = defaultdict(int)
            max_cnt = 0
            for j in range(i, -1, -1):
                cnt[s[j]] += 1
                if cnt[s[j]] > max_cnt:  # 手动 if 比大小
                    max_cnt = cnt[s[j]]
                if i - j + 1 == len(cnt) * max_cnt and f[j] + 1 < f[i + 1]:
                    f[i + 1] = f[j] + 1
        return f[n]


class Solution:
    def minimumSubstringsInPartition(self, s: str) -> int:
        @cache  
        def dfs(i: int) -> int:
            if i < 0:
                return 0
            res = inf
            cnt = defaultdict(int)
            max_cnt = 0
            for j in range(i, -1, -1):
                cnt[s[j]] += 1
                max_cnt = max(max_cnt, cnt[s[j]])
                if i - j + 1 == len(cnt) * max_cnt:
                    res = min(res, dfs(j - 1) + 1)
            return res

        return dfs(len(s) - 1)
