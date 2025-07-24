from functools import cache
from typing import List


class Solution:
    def predictTheWinner(self, nums: List[int]) -> bool:
        n = len(nums)

        # dp[i][j] 表示在区间 [i,j] 中，当前玩家比对手多拿的最大分数
        @cache
        def dfs(i: int, j: int) -> int:
            if i == j:
                return nums[i]

            # 当前玩家可以选择 nums[i] 或 nums[j]
            # 选择后，对手会在剩余区间中最优化自己的选择
            take_left = nums[i] - dfs(i + 1, j)
            take_right = nums[j] - dfs(i, j - 1)

            return max(take_left, take_right)

        return dfs(0, n - 1) >= 0
