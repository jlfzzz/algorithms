from cmath import inf
from typing import List


class Solution:
    def maxPossibleScore(self, start: List[int], d: int) -> int:
        start.sort()
        n = len(start)

        def check(target: int) -> bool:
            x = -inf
            for s in start:
                x = max(x + target, s)
                if x > s + d:
                    return False
            return True

        lo = 0
        hi = int(1e10)
        ans = 0
        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                lo = mid + 1
                ans = mid
            else:
                hi = mid
        return ans
