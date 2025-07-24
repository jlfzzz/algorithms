from typing import List
from bisect import *


class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        ans = []
        for x in nums:
            i = bisect_left(ans, x)
            if i == len(ans):
                ans.append(x)
            else:
                ans[i] = x
        return len(ans)
