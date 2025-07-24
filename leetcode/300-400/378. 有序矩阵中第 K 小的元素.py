from typing import List
from bisect import *


class Solution:
    def kthSmallest(self, matrix: List[List[int]], k: int) -> int:
        lo = matrix[0][0]
        hi = matrix[-1][-1] + 1
        ans = 0

        def count_less_equal(target: int) -> int:
            cnt = 0
            for row in matrix:
                if row[0] > target:
                    break
                cnt += bisect_right(row, target)
            return cnt

        while lo < hi:
            mid = (lo + hi) // 2
            if count_less_equal(mid) >= k:
                hi = mid
                ans = mid
            else:
                lo = mid + 1

        return ans
