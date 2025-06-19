from typing import List


class Solution:
    def minSizeSubarray(self, nums: List[int], target: int) -> int:
        n = len(nums)
        s1 = sum(nums)
        s2 = target % s1
        m = target // s1 * n
        s3 = s1 - s2

        left = 0
        s = 0
        ans_ = -1
        for right in range(2 * n):
            s += nums[right % n]
            while s > s3:
                s -= nums[left % n]
                left += 1
            if s == s3:
                ans_ = max(ans_, right - left + 1)
        return -1 if ans_ == -1 else m + n - ans_
