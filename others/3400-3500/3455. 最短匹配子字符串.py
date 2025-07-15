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
    def shortestMatchingSubstring(self, S: str, p: str) -> int:
        n = len(S)
        s1, s2, s3 = p.split("*")

        # next数组
        def compute_prefix_function(pattern: str) -> List[int]:
            m = len(pattern)
            pi = [0] * m
            j = 0
            for i in range(1, m):
                while j > 0 and pattern[i] != pattern[j]:
                    j = pi[j - 1]
                if pattern[i] == pattern[j]:
                    j += 1
                pi[i] = j
            return pi

        # 找所有出现的位置
        def kmp_search_all(text: str, pattern: str, pi: List[int]) -> List[int]:
            n, m = len(text), len(pattern)
            if m == 0:
                return list(range(n + 1))

            res = []
            j = 0
            for i in range(n):
                while j > 0 and text[i] != pattern[j]:
                    j = pi[j - 1]
                if text[i] == pattern[j]:
                    j += 1
                if j == m:
                    res.append(i - m + 1)
                    j = pi[j - 1]
            return res

        def get_next(s: str) -> List[int]:
            n = len(s)
            next = [0] * n
            length = 0
            i = 1
            while i < n:
                while length > 0 and s[i] != s[length]:
                    length = next[length - 1]

                if s[i] == s[length]:
                    length += 1
                next[i] = length
                i += 1
            return next

        def get_all_pos(pattern: str, next: List[int]) -> List[int]:
            m = len(pattern)
            if m == 0:
                return [i for i in range(n + 1)]
            ret = []
            j = 0
            for i, c in enumerate(S):
                while j > 0 and c != pattern[j]:
                    j = next[j - 1]
                if c == pattern[j]:
                    j += 1

                if j == m:
                    ret.append(i - m + 1)
                    j = next[j - 1]
            return ret

        nxt1, nxt2, nxt3 = (
            compute_prefix_function(s1),
            compute_prefix_function(s2),
            compute_prefix_function(s3),
        )
        pos1, pos2, pos3 = (
            kmp_search_all(S, s1, nxt1),
            kmp_search_all(S, s2, nxt2),
            kmp_search_all(S, s3, nxt3),
        )

        ans = n + n
        i, j, k = 0, 0, 0
        n1, n2, n3 = len(pos1), len(pos2), len(pos3)
        m1, m2, m3 = len(s1), len(s2), len(s3)
        while i < n1:
            while j < n2 and pos2[j] < pos1[i] + m1:
                j += 1
            if j == n2:
                break
            while k < n3 and pos3[k] < pos2[j] + m2:
                k += 1
            if k == n3:
                break
            ans = min(ans, pos3[k] + m3 - pos1[i])
            i += 1
        return ans if ans != n + n else -1


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
        s1, s2, s3 = p.split("*")

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
