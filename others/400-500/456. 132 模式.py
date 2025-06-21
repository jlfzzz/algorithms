from typing import List


class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        n = len(nums)
        if n < 3:
            return False

        # 左侧最小值
        left_min = nums[0]
        # 右侧所有元素
        right_all = SortedList(nums[2:])

        for j in range(1, n - 1):
            if left_min < nums[j]:
                index = right_all.bisect_right(left_min)
                if index < len(right_all) and right_all[index] < nums[j]:
                    return True
            left_min = min(left_min, nums[j])
            right_all.remove(nums[j + 1])

        return False


class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        stack = []
        third = float("-inf")  # 相当于 nums[k]

        for i in range(len(nums) - 1, -1, -1):
            if nums[i] < third:
                return True  # 找到 nums[i] < nums[k] < nums[j]
            while stack and nums[i] > stack[-1]:
                third = stack.pop()
            stack.append(nums[i])

        return False


class Solution:
    def find132pattern(self, nums: List[int]) -> bool:
        n = len(nums)
        # 单调栈，存储的是下标
        stk = [0]
        # min value, minv[j] 表示 a[0..j] 中的最小值
        minv = [nums[0]]

        for k in range(1, n):
            while stk and nums[stk[-1]] <= nums[k]:
                stk.pop()
            # 如果栈不为空，那么此时栈顶元素 stk[-1] 即为 j
            if stk and minv[stk[-1]] < nums[k]:
                return True
            stk.append(k)
            minv.append(min(minv[-1], nums[k]))

        return False
