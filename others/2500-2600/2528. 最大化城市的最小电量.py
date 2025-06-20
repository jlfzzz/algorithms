from typing import List


class Solution:
    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        n = len(stations)
        lo = min(stations)
        ans = lo
        hi = int(2e10)
        prefix = [0] * (n + 1)

        for i, x in enumerate(stations):
            prefix[i + 1] = prefix[i] + x

        cnt = [0] * n
        for i, x in enumerate(stations):
            cnt[i] = prefix[min(n, i + 1 + r)] - prefix[max(0, i - r)]

        while lo < hi:
            mid = (lo + hi) // 2

            def check(target: int) -> bool:
                used = 0
                diff = [0] * (n + 1)
                accumulate = 0
                for i, x in enumerate(stations):
                    accumulate += diff[i]
                    curr = cnt[i] + accumulate
                    if curr < target:
                        if used >= k:
                            return False
                        d = target - curr
                        if k - used < d:
                            return False
                        used += d
                        diff[i + 1] += d
                        diff[min(n, i + 2 * r + 1)] -= d

                return True

            if check(mid):
                ans = mid
                lo = mid + 1
            else:
                hi = mid
        return ans
