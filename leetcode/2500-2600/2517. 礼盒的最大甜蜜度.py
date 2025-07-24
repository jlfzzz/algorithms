from bisect import bisect_left
from typing import List


class Solution:
    def maximumTastiness(self, price: List[int], k: int) -> int:
        price.sort()

        lo = 0
        hi = price[-1] - price[0] + 1
        ans = 0
        n = len(price)

        def check(target: int) -> bool:
            cnt = 1
            prev = price[0]
            for i in range(1, n):
                if price[i] - prev >= target:
                    cnt += 1
                    prev = price[i]
            return cnt >= k

        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                lo = mid + 1
                ans = mid
            else:
                hi = mid
        return ans


class Solution:
    def maximumTastiness(self, price: List[int], k: int) -> int:
        def check(d: int) -> bool:
            # 二分最小的 f(d+1) < k，从而知道最大的 f(d) >= k
            d += 1
            cnt = 1
            pre = price[0]  # 先选一个最小的甜蜜度
            for p in price:
                if p >= pre + d:  # 可以选
                    cnt += 1
                    pre = p  # 上一个选的甜蜜度
            return cnt < k

        price.sort()
        right = (price[-1] - price[0]) // (k - 1)
        return bisect_left(range(right), True, key=check)
