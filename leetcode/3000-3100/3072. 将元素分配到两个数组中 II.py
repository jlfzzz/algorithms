from bisect import bisect_left
from typing import List


class FenwickTree:
    def __init__(self, n: int) -> None:
        self.tree = [0] * (n + 1)

    def update(self, index: int, val: int) -> None:
        i = index + 1
        while i < len(self.tree):
            self.tree[i] += 1
            i += i & -i

    def pre(self, index: int) -> int:
        s = 0
        while index > 0:
            s += self.tree[index]
            index -= index & -index
        return s

    def query(self, index: int) -> int:
        return self.pre(index + 1)


class Solution:
    def resultArray(self, nums: List[int]) -> List[int]:
        arr1 = [nums[0]]
        arr2 = [nums[1]]

        temp = sorted(list(set(nums)))
        m = len(temp)
        n = len(nums)

        ft1 = FenwickTree(m)
        ft2 = FenwickTree(m)

        p1 = bisect_left(temp, nums[0])
        p2 = bisect_left(temp, nums[1])

        ft1.update(p1, 1)
        ft2.update(p2, 1)

        for i in range(2, n):
            x = nums[i]
            p = bisect_left(temp, x)

            d1 = len(arr1) - ft1.query(p)
            d2 = len(arr2) - ft2.query(p)

            if d1 < d2 or (d1 == d2 and len(arr2) < len(arr1)):
                arr2.append(x)
                ft2.update(p, 1)
            else:
                arr1.append(x)
                ft1.update(p, 1)
        return arr1 + arr2

