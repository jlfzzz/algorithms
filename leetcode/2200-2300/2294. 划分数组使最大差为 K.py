from typing import List


class Solution:
    def partitionArray(self, nums: List[int], k: int) -> int:
        nums.sort()
        ans = 1
        prev = nums[0]
        n = len(nums)

        for i, x in enumerate(nums):

            if x - prev > k:
                prev = x
                ans += 1
        return ans
