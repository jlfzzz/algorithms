from typing import List

MOD = int(1e9 + 7)


class FenwickTree:
    def __init__(self, n: int, mx: int) -> None:
        self.tree = [0] * (n + 5)
        self.mx = mx

    def update(self, index: int, val: int) -> None:
        i = index + 1
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i

    def pre(self, index: int) -> int:
        s = 0
        while index > 0:
            s += self.tree[index]
            index &= index - 1
        return s

    def queryGreater(self, val: int) -> int:
        return self.pre(self.mx + 1) - self.pre(val + 1)

    def queryLesser(self, val: int) -> int:
        return self.pre(val)


class Solution:
    def createSortedArray(self, instructions: List[int]) -> int:
        ft = FenwickTree(max(instructions), max(instructions))
        ans = 0

        for i, x in enumerate(instructions):
            ans = (ans + min(ft.queryGreater(x), ft.queryLesser(x))) % MOD
            ft.update(x, 1)
        return ans
