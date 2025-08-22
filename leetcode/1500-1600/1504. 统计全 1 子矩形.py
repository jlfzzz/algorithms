from typing import List


class Solution:
    def numSubmat(self, mat: List[List[int]]) -> int:
        m, n = len(mat), len(mat[0])
        ans = 0
        cnt = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                if mat[i][j]:
                    cnt[i][j] = 1 if j == 0 else 1 + cnt[i][j - 1]
        
        for i in range(m):
            for j in range(n):
                t = inf
                for k in range(i, -1, -1):
                    t = min(t, cnt[k][j])
                    ans += t
        return ans
