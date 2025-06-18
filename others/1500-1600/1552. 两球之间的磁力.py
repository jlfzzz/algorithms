from typing import List


class Solution:
    def maxDistance(self, position: List[int], m: int) -> int:
        position.sort()
        lo = 1
        hi = (position[-1] - position[0]) // (m - 1) + 1
        n = len(position)

        def check(target: int) -> bool:
            cnt = 1
            prev = position[0]
            for i in range(1, n):
                if position[i] - prev >= target:
                    cnt += 1
                    prev = position[i]
            return cnt >= m

        ans = 1
        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                ans = mid
                lo = mid + 1
            else:
                hi = mid
        return ans
