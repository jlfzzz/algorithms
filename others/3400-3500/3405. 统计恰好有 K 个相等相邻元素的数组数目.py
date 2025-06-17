from functools import cache
from math import comb


class Solution:
    def countGoodArrays(self, n: int, m: int, k: int) -> int:
        MOD = 1_000_000_007
        return comb(n - 1, k) % MOD * m * pow(m - 1, n - k - 1, MOD) % MOD

# 超时爆内存
class Solution:
    def countGoodArrays(self, n: int, m: int, k: int) -> int:
        mod = int(1e9 + 7)
        @cache
        def dfs(i: int, x: int, j: int) -> int:
            if i == n:
                if j == k:
                    return 1
                return 0

            res = 0
            for y in range(1, m + 1):
                if y == x:
                    res = (res + dfs(i + 1, y, j + 1)) % mod
                else:
                    res = (res + dfs(i + 1, y, j)) % mod
            return res

        return dfs(0,-1,0) % mod
