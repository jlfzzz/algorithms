from cmath import inf
from typing import List


class Solution:
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:
        n = len(nums)
        ans = [i for i in range(n) if key in nums[max(i - k, 0) : min(n, i + k + 1)]]
        return ans


class Solution:
    def findKDistantIndices(self, nums: List[int], key: int, k: int) -> List[int]:
        last = -inf
        for i in range(k - 1, -1, -1):
            if nums[i] == key:
                last = i
                break

        ans = []
        n = len(nums)
        for i in range(n):
            if i + k < n and nums[i + k] == key:
                last = i + k
            if last >= i - k:  # key 在窗口中
                ans.append(i)
        return ans
