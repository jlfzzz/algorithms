from typing import List


class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        ans = [[] for _ in range(numRows)]
        for i in range(numRows):
            ans[i].append(1)
            for j in range(1, i):
                ans[i].append(ans[i - 1][j - 1] + ans[i - 1][j])
            if i != 0:
                ans[i].append(1)
        return ans
