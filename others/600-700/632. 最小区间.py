from heapq import *
from typing import List


class Solution:
    def smallestRange(self, nums: List[List[int]]) -> List[int]:
        arr = sorted((x, i) for i, arrr in enumerate(nums) for x in arrr)
        ans_l = -1
        ans_r = 999999999
        n = len(nums)
        cnt = [0] * n
        matches = 0
        left = 0
        for right, i in arr:
            if cnt[i] == 0:
                matches += 1
            cnt[i] += 1
            while matches == n:
                l, j = arr[left]
                if right - l < ans_r - ans_l:
                    ans_l, ans_r = l, right
                cnt[j] -= 1
                if cnt[j] == 0:
                    matches -= 1
                left += 1
        return [ans_l, ans_r]


class Solution:
    def smallestRange(self, nums: List[List[int]]) -> List[int]:
        # 把每个列表的第一个元素入堆
        h = [(arr[0], i, 0) for i, arr in enumerate(nums)]
        heapify(h)

        ans_l = h[0][0]  # 第一个合法区间的左端点
        ans_r = r = max(arr[0] for arr in nums)  # 第一个合法区间的右端点
        while h[0][2] + 1 < len(nums[h[0][1]]):  # 堆顶列表有下一个元素
            _, i, j = h[0]
            x = nums[i][j + 1]  # 堆顶列表的下一个元素
            heapreplace(h, (x, i, j + 1))  # 替换堆顶
            r = max(r, x)  # 更新合法区间的右端点
            l = h[0][0]  # 当前合法区间的左端点
            if r - l < ans_r - ans_l:
                ans_l, ans_r = l, r
        return [ans_l, ans_r]
