from functools import cache


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


class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        if int(s) > finish:
            return 0

        s1 = str(start)
        s2 = str(finish)
        n = len(s2)
        s1 = "0" * (n - len(s1)) + s1
        m = len(s)

        @cache
        def dfs(i: int, is_hi: bool, is_lo: bool):
            if i == n:
                return 1

            lo = 0
            hi = limit
            origin_hi = ord(s2[i]) - ord("0")
            origin_lo = ord(s1[i]) - ord("0")
            if is_hi:
                hi = min(hi, ord(s2[i]) - ord("0"))
            if is_lo:
                lo = ord(s1[i]) - ord("0")

            res = 0
            if i >= n - m:
                temp = ord(s[i - n + m]) - ord("0")
                if is_hi and temp > hi:
                    return 0
                hi = temp

                if is_lo and temp < lo:
                    return 0
                lo = temp

            for j in range(lo, hi + 1):
                res += dfs(i + 1, is_hi and j == origin_hi, is_lo and j == origin_lo)
            return res

        return dfs(0, True, True)


class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        if int(s) > finish:
            return 0

        s1 = str(start)
        s2 = str(finish)
        n = len(s2)
        s1 = "0" * (n - len(s1)) + s1
        m = len(s)

        memo = {}

        def dfs(i: int, is_hi: bool, is_lo: bool) -> int:
            key = (i, is_hi, is_lo)
            if key in memo:
                return memo[key]

            if i == n:
                return 1

            lo = 0
            hi = limit
            origin_hi = int(s2[i])
            origin_lo = int(s1[i])
            if is_hi:
                hi = min(hi, origin_hi)
            if is_lo:
                lo = origin_lo

            res = 0
            # 如果当前位置属于后缀部分，强制匹配 s
            if i >= n - m:
                required = int(s[i - (n - m)])
                if required < lo or required > hi:
                    memo[key] = 0
                    return 0
                res += dfs(
                    i + 1,
                    is_hi and required == origin_hi,
                    is_lo and required == origin_lo,
                )
            else:
                for digit in range(lo, hi + 1):
                    res += dfs(
                        i + 1,
                        is_hi and digit == origin_hi,
                        is_lo and digit == origin_lo,
                    )

            memo[key] = res
            return res

        return dfs(0, True, True)
