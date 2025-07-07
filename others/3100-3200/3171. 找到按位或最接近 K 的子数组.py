from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        ans = inf
        for i, x in enumerate(nums):
            ans = min(ans, abs(x - k))
            j = i - 1
            # 如果 x 是 nums[j] 的子集，就退出循环
            while j >= 0 and nums[j] | x != nums[j]:
                nums[j] |= x
                ans = min(ans, abs(nums[j] - k))
                j -= 1
        return ans


class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        left = 0
        cnt = defaultdict()
        curr = 0
        ans = inf
        for right, x in enumerate(nums):
            curr |= x
            for i in range(x.bit_length()):
                if x >> i & 1:
                    cnt[i] = right
            if curr == k:
                return 0
            ans = min(ans, abs(curr - k))
            while curr > k and left < right:
                for i in range(nums[left].bit_length()):
                    if nums[left] >> i & 1 and cnt[i] == left:
                        del cnt[i]
                        curr -= 1 << i
                if curr == k:
                    return 0
                ans = min(ans, abs(curr - k))
                left += 1
        return ans
