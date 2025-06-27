from typing import Counter, List


class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        s = set(nums)
        n = len(nums)
        ans = []
        path = []
        cnt = Counter(nums)

        def dfs(i: int):
            if i == n:
                ans.append(path.copy())
                return

            for x in s:
                if cnt[x] != 0:
                    cnt[x] -= 1
                    path.append(x)
                    dfs(i + 1)
                    path.pop()
                    cnt[x] += 1

        dfs(0)
        return ans


class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        cnt = Counter(nums)
        n = len(nums)
        s = set(nums)
        res = []
        path = []

        def dfs(i: int) -> None:
            if i >= n:
                res.append(path[:])
                return

            for num in s:
                if cnt[num] > 0:
                    cnt[num] -= 1
                    path.append(num)
                    dfs(i + 1)
                    path.pop()
                    cnt[num] += 1

        dfs(0)
        return res
