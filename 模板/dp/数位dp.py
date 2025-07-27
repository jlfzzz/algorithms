from functools import cache


# lc2999 上下界+后缀匹配+每位最多limit
class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        m = len(s)
        s1, s2 = str(start), str(finish)
        n = len(s2)
        s1 = "0" * (n - len(s1)) + s1

        @cache
        def dfs(i: int, is_lo: bool, is_hi: bool) -> int:
            if i == n:
                return 1

            lo = 0 if not is_lo else int(s1[i])
            hi = limit if not is_hi else min(int(s2[i]), limit)

            if i >= n - m:
                j = i - (n - m)
                x = int(s[j])
                if lo <= x <= hi:
                    return dfs(i + 1, is_lo and x == lo, is_hi and x == int(s2[i]))
                return 0

            res = 0
            for j in range(lo, hi + 1):
                res += dfs(i + 1, is_lo and j == lo, is_hi and j == int(s2[i]))
            return res

        return dfs(0, True, True)
