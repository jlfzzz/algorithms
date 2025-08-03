from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def maxSumTrionic(self, nums: List[int]) -> int:
        n = len(nums)
        i = 0
        pos = []
        while i < n:
            begin = i
            i += 1
            while i < n and nums[i] > nums[i - 1]:
                i += 1
            if i == n:
                break
            if i - begin == 1:
                continue

            second = i
            while i < n and nums[i] < nums[i - 1]:
                i += 1
            if i == n:
                break
            if i == second:
                continue

            third = i
            while i < n and nums[i] > nums[i - 1]:
                i += 1
            if i == third:
                continue

            third_end = i - 1
            pos.append((begin, second, third, third_end))

            i = third - 1

        pre = [0] * (n + 1)
        for i, x in enumerate(nums):
            pre[i + 1] = pre[i] + x
        ans = -inf
        for begin, second, third, third_end in pos:
            middle_sum = pre[third] - pre[second - 1]
            left = -inf
            curr = 0
            for i in range(second - 2, begin - 1, -1):
                curr += nums[i]
                left = max(left, curr)
            right = -inf
            curr = 0
            for i in range(third, third_end + 1):
                curr += nums[i]
                right = max(right, curr)

            total = middle_sum + left + right
            ans = max(ans, total)

        return ans

def main():
    s = SortedList([3, 1, 2])
    print(s)  # 输出 SortedList([1, 2, 3])

if __name__ == "__main__":
    main()