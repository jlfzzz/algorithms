from typing import List


class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        ans = -1
        s = set()
        for x in nums:
            if -x in s:
                ans = max(ans, abs(x))
            s.add(x)
        return ans
