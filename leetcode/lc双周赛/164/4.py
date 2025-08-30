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
    def minOperations(self, s: str, k: int) -> int:
        n = len(s)
        cnt0 = s.count("0")
        drunepalix = (s, k)
        if cnt0 == 0:
            return 0
        if k == n:
            if cnt0 == n:
                return 1
            return -1

        @cache
        def rng(cur: int) -> Tuple[int, int, int]:
            ones = n - cur
            zmax = min(k, cur)
            zmin = max(0, k - ones)
            L = cur + k - 2 * zmax
            R = cur + k - 2 * zmin
            p = (cur + k) & 1
            return L, R, p

        vis = [False] * (n + 1)
        vis[cnt0] = True

        tmax0 = n // 2
        tmax1 = (n - 1) // 2
        par0 = list(range(tmax0 + 2))
        par1 = list(range(tmax1 + 2))

        def find(par: List[int], i: int) -> int:
            while i < len(par) and par[i] != i:
                par[i] = par[par[i]]
                i = par[i]
            return i

        def remove_value(v: int) -> None:
            if v < 0 or v > n:
                return
            if (v & 1) == 0:
                t = v >> 1
                if t <= tmax0:
                    par0[t] = find(par0, t + 1)
            else:
                t = (v - 1) >> 1
                if t <= tmax1:
                    par1[t] = find(par1, t + 1)

        remove_value(cnt0)

        from collections import deque

        q = deque([cnt0])
        step = 0
        while q:
            for _ in range(len(q)):
                cur = q.popleft()
                if cur == 0:
                    return step
                L, R, p = rng(cur)
                if p == 0:
                    v = L if (L & 1) == 0 else L + 1
                    if v <= R:
                        t = v >> 1
                        t_end = R >> 1
                        while True:
                            t = find(par0, t)
                            if t > t_end:
                                break
                            nv = t << 1
                            if not vis[nv]:
                                vis[nv] = True
                                q.append(nv)
                            par0[t] = find(par0, t + 1)
                            t = par0[t]
                else:
                    v = L if (L & 1) == 1 else L + 1
                    if v <= R:
                        t = (v - 1) >> 1
                        t_end = (R - 1) >> 1
                        while True:
                            t = find(par1, t)
                            if t > t_end:
                                break
                            nv = (t << 1) + 1
                            if not vis[nv]:
                                vis[nv] = True
                                q.append(nv)
                            par1[t] = find(par1, t + 1)
                            t = par1[t]
            step += 1
        return -1
