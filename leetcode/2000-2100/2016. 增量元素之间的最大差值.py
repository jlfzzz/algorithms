from typing import List


class Solution:

    def maximumDifference(self, nums: List[int]) -> int:
        ans = -10000000
        mn = nums[0]
        n = len(nums)

        for i in range(1, n):
            if nums[i] > mn:
                ans = max(ans, nums[i] - mn)
            mn = min(mn, nums[i])
        return ans if ans != -10000000 else -1
