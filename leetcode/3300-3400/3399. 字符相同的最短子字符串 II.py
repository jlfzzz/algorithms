# 常用内建库
import math
import bisect
import heapq
import itertools
import collections
import functools
import operator
import random
import statistics
import string

# 快捷方式导出
from math import gcd, lcm, ceil, floor, sqrt
from bisect import bisect_left, bisect_right, insort
from heapq import heappush, heappop, heapify
from collections import deque, Counter, defaultdict
from functools import lru_cache, cmp_to_key
from itertools import permutations, combinations, accumulate, product
from typing import List

class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        cnt = 0

        for i in range(n):
            if int(s[i]) != i & 1:
                cnt += 1
        if min(cnt, n - cnt) <= numOps:
            return 1

        lo = 2
        hi = n + 1

        def check(limit: int) -> bool:
            used = 0
            cnt = 1
            prev = int(s[0])
            i = 1
            while i < n:
                curr = int(s[i])
                if i == n - 1 or curr != prev:
                    if curr != prev:
                        used += cnt // (limit + 1)
                        cnt = 1
                        prev = curr
                    else:
                        cnt += 1
                        used += cnt // (limit + 1)
                else:
                    cnt += 1
                i += 1

            return used <= numOps

        while lo < hi:
            mid = (lo + hi) // 2

            if check(mid):
                ans = mid
                hi = mid
            else:
                lo = mid + 1
        return ans

class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        def check(m: int) -> bool:
            cnt = 0
            if m == 1:
                cnt = sum((ord(b) ^ i) & 1 for i, b in enumerate(s))
                cnt = min(cnt, n - cnt)
            else:
                k = 0
                for i, b in enumerate(s):
                    k += 1
                    if i == n - 1 or b != s[i + 1]:
                        cnt += k // (m + 1)
                        k = 0
            return cnt <= numOps
        return bisect.bisect_left(range(n), True, 1, key=check)

class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        cnt = sum((ord(s[i]) ^ i) & 1 for i in range(len(s)))
        if min(cnt, len(s) - cnt) <= numOps:
            return 1

        heap = []
        cnt = 0
        n = len(s)
        for i, c in enumerate(s):
            cnt += 1
            if i == n - 1 or c != s[i + 1]:
                heapq.heappush(heap, (-cnt, cnt, 1))
                cnt = 0

        while numOps and heap:
            neg_len, total_len, parts = heapq.heappop(heap)
            if neg_len == -2:
                return 2
            parts += 1

            new_len = total_len // parts
            heapq.heappush(heap, (-new_len, total_len, parts))
            numOps -= 1

        # 操作完后堆顶就是最小段最大长度
        return -heap[0][0]
