from functools import cache

MOD = int(1e9 + 7)

# 骑士的8个移动方向
DIR = [(1, 2), (1, -2), (-1, 2), (-1, -2), (2, 1), (2, -1), (-2, 1), (-2, -1)]


class Solution:
    def knightDialer(self, n: int) -> int:
        ans = 0

        def ok(i, j):
            # 检查位置是否在有效的数字键盘上
            # 数字键盘布局：
            # 1 2 3
            # 4 5 6
            # 7 8 9
            #   0
            if i == 3 and (j == 0 or j == 2):  # 位置(3,0)和(3,2)无效
                return False
            return 0 <= i <= 3 and 0 <= j <= 2

        @cache
        def dfs(m: int, i: int, j: int) -> int:
            if m == n:
                return 1
            res = 0
            for dx, dy in DIR:
                new_x, new_y = i + dx, j + dy
                if ok(new_x, new_y):
                    res = (res + dfs(m + 1, new_x, new_y)) % MOD
            return res

        # 遍历所有有效的起始位置
        for i in range(4):
            for j in range(3):
                if ok(i, j):
                    ans = (ans + dfs(1, i, j)) % MOD

        return ans
