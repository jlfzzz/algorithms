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
    def minimumBeautifulSubstrings(self, s: str) -> int:
        n = len(s)
        dp = [inf] * (n + 1)
        dp[n] = 0
        st = set()
        base = 1
        for i in range(10):
            st.add(base)
            base *= 5
        for i in range(n - 1, -1, -1):
            if s[i] == "0":
                continue
            for j in range(i + 1, n + 1):
                if int(s[i:j], 2) in st:
                    dp[i] = min(dp[i], dp[j] + 1)
        return dp[0] if dp[0] != inf else -1


# 预处理 2**15 以内的 5 的幂
pow5 = [bin(5**i)[2:] for i in range(7)]


class Solution:
    def minimumBeautifulSubstrings(self, s: str) -> int:
        n = len(s)

        @cache
        def dfs(i: int) -> int:
            if i == n:
                return 0
            if s[i] == "0":
                return inf  # 不能包含前导 0
            res = inf
            for t in pow5:
                if i + len(t) > n:
                    break
                if s[i : i + len(t)] == t:  # 忽略切片的时间，这里的比较视作均摊 O(1)
                    res = min(res, dfs(i + len(t)) + 1)
            return res

        ans = dfs(0)
        return ans if ans < inf else -1


class Solution:
    def minimumBeautifulSubstrings(self, s: str) -> int:
        n = len(s)

        def check(x: int) -> bool:
            if x <= 0:
                return False
            if x == 1:
                return True
            while x % 5 == 0:
                x //= 5
            return x == 1

        def dfs(i: int, path: str) -> int:
            if i == n:
                if len(path) == 0:
                    return 0
                if path[0] == "0":
                    return float("inf")
                x = int(path, 2)
                return 1 if check(x) else float("inf")

            if path == "" and s[i] == "0":
                return float("inf")

            path += s[i]

            if path[0] == "0":
                return float("inf")

            x = int(path, 2)

            res = dfs(i + 1, path)
            if check(x):
                res = min(res, 1 + dfs(i + 1, ""))

            return res

        ans = dfs(0, "")
        return -1 if ans == float("inf") else ans
