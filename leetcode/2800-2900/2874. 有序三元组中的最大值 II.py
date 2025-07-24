from math import inf
from typing import List


class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        n = len(nums)
        suf_max = [0] * (n + 1)
        for i in range(n - 1, 1, -1):
            suf_max[i] = max(suf_max[i + 1], nums[i])

        ans = pre_max = 0
        for j, x in enumerate(nums):
            ans = max(ans, (pre_max - x) * suf_max[j + 1])
            pre_max = max(pre_max, x)
        return ans


class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        ans = max_diff = pre_max = 0
        for x in nums:
            ans = max(ans, max_diff * x)
            max_diff = max(max_diff, pre_max - x)
            pre_max = max(pre_max, x)
        return ans


# 题目都是正数，不用维护最小值负数

class Solution:
    def maximumTripletValue(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0

        # 后缀最大和最小
        suf = [[-inf, inf] for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            suf[i][0] = max(suf[i + 1][0], nums[i])
            suf[i][1] = min(suf[i + 1][1], nums[i])

        pre_max = nums[0]
        pre_min = nums[0]
        for j in range(1, n - 1):
            x = nums[j]
            for z in suf[j + 1]:  # 后缀最大值或最小值
                ans = max(ans, (pre_max - x) * z)
                ans = max(ans, (pre_min - x) * z)

            pre_max = max(pre_max, x)
            pre_min = min(pre_min, x)

        return ans
