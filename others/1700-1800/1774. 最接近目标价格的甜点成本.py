from typing import List


class Solution:
    def closestCost(
        self, baseCosts: List[int], toppingCosts: List[int], target: int
    ) -> int:
        dp = [False] * (100002)
        dp[0] = True

        for topping in toppingCosts:
            for k in range(100001, topping - 1, -1):
                dp[k] |= dp[k - topping]
                if k - topping - topping >= 0:
                    dp[k] |= dp[k - topping - topping]
        ans = 10000000
        for base in baseCosts:
            for i in range(100001, base - 1, -1):
                if dp[i - base] and abs(target - i) <= abs(target - ans):
                    if abs(target - i) == abs(target - ans):
                        if i < ans:
                            ans = i
                    else:
                        ans = i

        return ans
