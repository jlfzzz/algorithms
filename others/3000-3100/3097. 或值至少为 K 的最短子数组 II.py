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
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        ans = inf
        for i, x in enumerate(nums):
            if x >= k:
                return 1
            j = i - 1
            while j >= 0 and nums[j] | x != nums[j]:
                nums[j] |= x
                if nums[j] >= k:
                    ans = min(ans, i - j + 1)
                j -= 1
        return ans if ans < inf else -1
                                                                