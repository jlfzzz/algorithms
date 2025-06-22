from typing import List


class NumArray:

    def __init__(self, nums: List[int]):
        n = len(nums)
        self.nums = [0] * n
        self.tree = [0] * (n + 1)
        for i, x in enumerate(nums):
            self.update(i, x)

    def update(self, index: int, val: int) -> None:
        delta = val - self.nums[index]
        self.nums[index] = val
        i = index + 1
        while i < len(self.tree):
            self.tree[i] += delta
            i += i & -i

    def prefixSum(self, i:int)->int:
        s = 0
        while i:
            s += self.tree[i]
            i -= i & -i
        return s

    def sumRange(self, left: int, right: int) -> int:
        return self.prefixSum(right + 1) - self.prefixSum(left)


# Your NumArray object will be instantiated and called as such:
# obj = NumArray(nums)
# obj.update(index,val)
# param_2 = obj.sumRange(left,right)