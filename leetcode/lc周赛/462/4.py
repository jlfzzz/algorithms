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
    def specialPalindrome(self, n: int) -> int:
        arr = set()

        def f(s: str):
            cnt = Counter(s)
            m = len(s)
            extra = ""

            for key in cnt.keys():
                if cnt[key] & 1:
                    cnt[key] -= 1
                    extra = key
                cnt[key] //= 2

            if m // 2 == 0:
                if extra:
                    arr.add(int(extra))
                return

            def dfs(x: int):
                if len(str(x)) == m // 2:
                    t = str(x)
                    if m & 1:
                        t += extra
                    t += str(x)[::-1]
                    arr.add(int(t))
                    return

                for k, v in cnt.items():
                    if v > 0:
                        cnt[k] -= 1
                        dfs(x * 10 + int(k))
                        cnt[k] += 1

            for k, v in list(cnt.items()):
                if v > 0:
                    cnt[k] -= 1
                    dfs(int(k))
                    cnt[k] += 1

        for i in range(1, 1 << 9):
            s = ""
            odd = False
            flag = True
            for j in range(9):
                if (1 << j) & i:
                    if (j + 1) % 2 == 1:
                        if odd:
                            flag = False
                            break
                        else:
                            odd = True
                    s += str(j + 1) * (j + 1)

            if len(s) >= 16 or not flag:
                continue

            f(s)

        arr = sorted(list(arr))
        idx = bisect_left(arr, n)
        if arr[idx] == n:
            idx += 1
            
        return arr[idx]
