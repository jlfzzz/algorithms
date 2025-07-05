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
    def calc_pi(self, p: str) -> List[int]:
        pi = [0] * len(p)
        cnt = 0
        for i in range(1, len(p)):
            v = p[i]
            while cnt > 0 and p[cnt] != v:
                cnt = pi[cnt - 1]
            if p[cnt] == v:
                cnt += 1
            pi[i] = cnt
        return pi

    # 在文本串 s 中查找模式串 p，返回所有成功匹配的位置（p[0] 在 s 中的下标）
    def kmp_search(self, s: str, p: str) -> List[int]:
        if not p:
            # s 的所有位置都能匹配空串，包括 len(s)
            return list(range(len(s) + 1))

        pi = self.calc_pi(p)
        pos = []
        cnt = 0
        for i, v in enumerate(s):
            while cnt > 0 and p[cnt] != v:
                cnt = pi[cnt - 1]
            if p[cnt] == v:
                cnt += 1
            if cnt == len(p):
                pos.append(i - len(p) + 1)
                cnt = pi[cnt - 1]
        return pos
    def shortestMatchingSubstring(self, s: str, p: str) -> int:
        s1, s2, s3 = p.split('*')

        # 三段各自在 s 中的所有匹配位置
        l1 = self.kmp_search(s, s1)
        l2 = self.kmp_search(s, s2)
        l3 = self.kmp_search(s, s3)
        ans = inf
        i, j, k = 0, 0, 0
        while i < len(l1):
            x = l1[i]
            r1 = x + len(s1)
            while j < len(l2) and l2[j] < r1:
                j += 1
            if j != len(l2):
                y = l2[j]
                r2 = y + len(s2)
                while k < len(l3) and l3[k] < r2:
                    k += 1
                if k != len(l3):
                    z = l3[k]
                    ans = min(ans, z + len(s3) - x)
            i += 1
        return ans if ans != inf else -1

