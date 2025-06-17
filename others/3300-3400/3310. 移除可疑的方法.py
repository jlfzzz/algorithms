from typing import *


class Solution:
    def remainingMethods(
        self, n: int, k: int, invocations: List[List[int]]
    ) -> List[int]:
        g = [[] for _ in range(n)]
        for x, y in invocations:
            g[x].append(y)

        # 标记所有可疑方法
        is_suspicious = [False] * n

        def dfs(x: int) -> None:
            is_suspicious[x] = True
            for y in g[x]:
                if not is_suspicious[y]:  # 避免无限递归
                    dfs(y)

        dfs(k)

        # 检查是否有【非可疑方法】->【可疑方法】的边
        for x, y in invocations:
            if not is_suspicious[x] and is_suspicious[y]:
                # 无法移除可疑方法
                return list(range(n))

        # 移除所有可疑方法
        return [i for i, b in enumerate(is_suspicious) if not b]
