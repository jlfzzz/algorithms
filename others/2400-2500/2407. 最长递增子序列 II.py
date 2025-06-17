from typing import List


class Solution:
    def lengthOfLIS(self, nums: List[int], k: int) -> int:
        u = max(nums)
        mx = [0] * 4 * u

        def update(o: int, l: int, r: int, target: int, val: int) -> int:
            if l == r:
                mx[o] = val
                return
            mid = (l + r) // 2
            if target <= mid:
                update(o * 2, l, mid, target, val)
            else:
                update(o * 2 + 1, mid + 1, r, target, val)
            mx[o] = max(mx[o * 2], mx[o * 2 + 1])

        def query(o: int, l: int, r: int, L: int, R: int) -> int:
            if L <= l and R >= r:
                return mx[o]
            res = 0
            mid = (l + r) // 2
            if L <= mid:
                res = max(res, query(o * 2, l, mid, L, R))
            if R > mid:
                res = max(res, query(o * 2 + 1, mid + 1, r, L, R))
            return res

        for x in nums:
            if x == 1:
                update(1, 1, u, 1, 1)
            else:
                res = 1 + query(1, 1, u, max(1, x - k), x - 1)
                update(1, 1, u, x, res)
        return mx[1]


class Solution:
    def lengthOfLIS(self, nums: List[int], k: int) -> int:
        m = max(nums)
        mx = [0] * 4 * m

        def update(o, l, r, target, val):
            if l == r:
                mx[o] = val
                return
            mid = (l + r) // 2
            if target <= mid:
                update(o * 2, l, mid, target, val)
            else:
                update(o * 2 + 1, mid + 1, r, target, val)
            mx[o] = max(mx[o * 2], mx[o * 2 + 1])

        def query(o, l, r, L, R):
            if L <= l and R >= r:
                return mx[o]
            mid = (l + r) // 2
            res = 0
            if L <= mid:
                res = max(res, query(o * 2, l, mid, L, R))
            if R > mid:
                res = max(res, query(o * 2 + 1, mid + 1, r, L, R))
            return res

        for x in nums:
            if x == 1:
                update(1, 1, m, 1, 1)
            else:
                res = query(1, 1, m, max(x - k, 1), x - 1) + 1
                update(1, 1, m, x, res)
        return mx[1]
