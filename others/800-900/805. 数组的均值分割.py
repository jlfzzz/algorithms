from typing import List


class Solution:
    def splitArraySameAverage(self, nums: List[int]) -> bool:
        n = len(nums)
        m = n
        s = sum(nums)
        dp = [set() for _ in range(m + 1)]
        dp[0].add(0)
        for num in nums:
            for i in range(m - 1, 0, -1):
                for x in dp[i - 1]:
                    curr = x + num
                    if curr * n == s * i:
                        return True
                    dp[i].add(curr)
        return False

class Solution:
    def splitArraySameAverage(self, nums: List[int]) -> bool:
        n = len(nums)
        m = n // 2
        s = sum(nums)
        if all(s * i % n for i in range(1, m + 1)):
            return False

        dp = [set() for _ in range(m + 1)]
        dp[0].add(0)
        for num in nums:
            for i in range(m, 0, -1):
                for x in dp[i - 1]:
                    curr = x + num
                    if curr * n == s * i:
                        return True
                    dp[i].add(curr)
        return False


class Solution:
    def splitArraySameAverage(self, nums: List[int]) -> bool:
        s = sum(nums)
        n = len(nums)

        dp = [set() for _ in range(s + 1)]
        dp[0].add(0)

        for x in nums:
            for i in range(s, x - 1, -1):
                new_counts = set()
                for k in dp[i - x]:
                    new_count = k + 1
                    if (
                        new_count > 0
                        and new_count < n
                        and i * (n - new_count) == (s - i) * new_count
                    ):
                        return True
                    new_counts.add(new_count)
                dp[i].update(new_counts)

        return False


class Solution:
    def splitArraySameAverage(self, nums: List[int]) -> bool:
        n = len(nums)
        if n == 1:
            return False

        s = sum(nums)
        for i in range(n):
            nums[i] = nums[i] * n - s

        m = n // 2
        left = set()
        for i in range(1, 1 << m):
            tot = sum(x for j, x in enumerate(nums[:m]) if i >> j & 1)
            if tot == 0:
                return True
            left.add(tot)

        rsum = sum(nums[m:])
        for i in range(1, 1 << (n - m)):
            tot = sum(x for j, x in enumerate(nums[m:]) if i >> j & 1)
            if tot == 0 or rsum != tot and -tot in left:
                return True
        return False
