from typing import List
from collections import *


class Solution:
    def eventualSafeNodes(self, graph: List[List[int]]) -> List[int]:
        n = len(graph)
        # 0: 未访问, 1: 正在访问(当前路径中), 2: 已完成访问
        color = [0] * n

        def dfs(node: int) -> bool:
            if color[node] != 0:
                return color[node] == 2

            color[node] = 1  # 标记为正在访问

            for neighbor in graph[node]:
                if color[neighbor] == 1 or not dfs(neighbor):
                    # 发现环或邻居不安全
                    return False

            color[node] = 2  # 标记为安全
            return True

        result = []
        for i in range(n):
            if dfs(i):
                result.append(i)

        return result
