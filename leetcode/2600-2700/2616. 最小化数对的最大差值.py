from typing import List


class Solution:
    def minimizeMax(self, nums: List[int], p: int) -> int:
        nums.sort()
        ans = 100000000

        lo = 0
        hi = nums[-1] - nums[0] + 1
        n = len(nums)

        def check(limit) -> bool:
            cnt = 0
            i = 3
            dp = [0] * (n + 2)

            while i < n + 2:
                dp[i] = dp[i - 1]
                if nums[i - 2] - nums[i - 3] <= limit:
                    dp[i] = max(dp[i], dp[i - 2] + 1)
                i += 1

            return dp[-1] >= p

        while lo < hi:
            mid = (lo + hi) // 2

            if check(mid):
                ans = mid
                hi = mid
            else:
                lo = mid + 1

        return ans


class Solution:
    def minimizeMax(self, nums: List[int], p: int) -> int:
        nums.sort()
        ans = 100000000

        lo = 0
        hi = nums[-1] - nums[0] + 1
        n = len(nums)

        def check(limit) -> bool:
            cnt = 0
            i = 0
            while i < n - 1:
                if nums[i + 1] - nums[i] <= limit:
                    cnt += 1
                    i += 2  # 跳过下一对
                else:
                    i += 1

            return cnt >= p

        while lo < hi:
            mid = (lo + hi) // 2

            if check(mid):
                ans = mid
                hi = mid
            else:
                lo = mid + 1

        return ans
