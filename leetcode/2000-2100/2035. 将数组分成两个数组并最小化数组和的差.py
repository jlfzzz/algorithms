from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
MOD = int(1e9 + 7)


class Solution:
    def minimumDifference(self, nums: List[int]) -> int:
        n = len(nums) // 2
        total = sum(nums)

        def count(nums: List[int]) -> DefaultDict:
            ret = defaultdict(set)
            for i in range(1 << len(nums)):
                cnt = 0
                s = 0
                for j, x in enumerate(nums):
                    if i >> j & 1:
                        s += x
                        cnt += 1
                ret[cnt].add(s)
            return ret

        # 快一点
        def count(nums: List[int]) -> DefaultDict:
            ret = defaultdict(set)
            n = len(nums)
            for k in range(n + 1):
                for comb in combinations(nums, k):
                    ret[k].add(sum(comb))
            return ret

        left = count(nums[:n])
        right = count(nums[n:])
        for k in right:
            right[k] = sorted(right[k])
        ans = inf
        for k, left_sums in left.items():
            right_sums = right[n - k]
            for s1 in left_sums:
                target = total // 2 - s1
                idx = bisect_left(right_sums, target)
                # 检查 idx 和 idx - 1（防止漏最接近的）
                for j in [idx - 1, idx]:
                    if 0 <= j < len(right_sums):
                        s2 = right_sums[j]
                        s = s1 + s2
                        ans = min(ans, abs(total - 2 * s))
        return ans
