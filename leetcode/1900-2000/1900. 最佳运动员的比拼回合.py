from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def earliestAndLatest(
        self, n: int, firstPlayer: int, secondPlayer: int
    ) -> List[int]:

        @cache
        def dfs(x: int, y: int, curr: int) -> Tuple[int, int]:
            if x + y + 1 == curr:
                return (1, 1)

            m = curr // 2
            if x >= m:
                x, y = curr - 1 - x, curr - 1 - y

            mn = x
            mx = y
            if y >= m:
                mx = curr - 1 - y
            res1, res2 = INF, -INF
            # 左边删除i个
            for i in range(x + 1):
                # 中间删除j个
                for j in range(mx - mn):
                    t1, t2 = dfs(x - i, y - j - i, (curr + 1) // 2)
                    res1, res2 = Min(res1, t1 + 1), Max(res2, t2 + 1)
            return (res1, res2)

        result = dfs(firstPlayer - 1, secondPlayer - 1, n)
        return [result[0], result[1]]


class Solution:
    def earliestAndLatest(
        self, n: int, firstPlayer: int, secondPlayer: int
    ) -> List[int]:
        @cache  # 缓存装饰器，避免重复计算 dfs（一行代码实现记忆化）
        def dfs(n: int, first: int, second: int) -> Tuple[int, int]:
            # AB 相遇
            if first + second == n + 1:
                return 1, 1

            # 保证 A 左边人数比 B 右边人数少
            # 注：题目已保证 first < second
            if first + second > n + 1:
                first, second = n + 1 - second, n + 1 - first

            m = (n + 1) // 2  # 下一回合人数
            # AB 之间保留 [min_mid, max_mid) 个人
            min_mid = 0 if second <= m else second - n // 2 - 1
            max_mid = second - first if second <= m else m - first
            earliest, latest = inf, 0

            for left in range(first):  # 枚举 A 左侧保留 left 个人
                for mid in range(min_mid, max_mid):  # 枚举 AB 之间保留 mid 个人
                    # 无需枚举 B 右侧保留多少个人，因为剩下的 m-2-left-mid 个人都在 B 右侧
                    e, l = dfs(m, left + 1, left + mid + 2)
                    earliest = min(earliest, e)
                    latest = max(latest, l)

            # 加上当前回合
            return earliest + 1, latest + 1

        return list(dfs(n, firstPlayer, secondPlayer))


class Solution:
    def earliestAndLatest(
        self, n: int, firstPlayer: int, secondPlayer: int
    ) -> List[int]:
        self.n = n

        def list_to_mask(players: List[int]) -> int:
            mask = 0
            for player in players:
                mask |= 1 << (player - 1)
            return mask

        @cache
        def dfs(l: int):
            player_list = [(i + 1) for i in range(self.n) if l >> i & 1]
            n = len(player_list)
            m = n // 2
            for i in range(m):
                if (
                    player_list[i] == firstPlayer
                    and player_list[n - i - 1] == secondPlayer
                ) or (
                    player_list[i] == secondPlayer
                    and player_list[n - i - 1] == firstPlayer
                ):
                    return [1, 1]

            res = [10000, -10000]
            for i in range(1 << m):
                t = []
                for j in range(m):
                    if i >> j & 1:
                        if (
                            player_list[n - 1 - j] == firstPlayer
                            or player_list[n - 1 - j] == secondPlayer
                        ):
                            t.append(player_list[n - 1 - j])
                        else:
                            t.append(player_list[j])
                    else:
                        if (
                            player_list[j] == firstPlayer
                            or player_list[j] == secondPlayer
                        ):
                            t.append(player_list[j])
                        else:
                            t.append(player_list[n - 1 - j])
                if n % 2 == 1:
                    t.append(player_list[m])
                t.sort()
                next_mask = list_to_mask(t)
                ret = dfs(next_mask)
                if ret[0] + 1 < res[0]:
                    res[0] = ret[0] + 1
                if ret[1] + 1 > res[1]:
                    res[1] = ret[1] + 1
            return res

        return dfs((1 << n) - 1)
