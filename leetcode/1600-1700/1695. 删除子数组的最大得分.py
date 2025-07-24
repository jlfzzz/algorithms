from typing import List


class Solution:
    def maximumUniqueSubarray(self, nums: List[int]) -> int:
        window = set()
        left = 0
        s = 0
        ans = 0
        for right, x in enumerate(nums):
            while x in window:
                window.remove(nums[left])
                s -= nums[left]
                left += 1

            s += x
            window.add(x)
            ans = max(ans, s)
        return ans
