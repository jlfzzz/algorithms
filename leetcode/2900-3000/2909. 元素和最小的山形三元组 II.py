from typing import List
from collections import *


class Solution:
    def minimumSum(self, nums: List[int]) -> int:
        n = len(nums)
        suf = [10000000000] * (n + 1)
        x = 10000000000
        for i in range(n - 1, -1, -1):
            suf[i] = x
            x = min(x, nums[i])

        ans = 10000000000
        x = nums[0]
        for i in range(1, n):
            if nums[i] > x and nums[i] > suf[i]:
                ans = min(ans, nums[i] + x + suf[i])
            x = min(x, nums[i])
        return ans if ans != 10000000000 else -1
