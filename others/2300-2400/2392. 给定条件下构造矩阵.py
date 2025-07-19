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
    def buildMatrix(
        self, k: int, rowConditions: List[List[int]], colConditions: List[List[int]]
    ) -> List[List[int]]:

        def topological_sort(conditions):
            graph = [[] for _ in range(k)]
            indegree = [0] * k

            for a, b in conditions:
                a, b = a - 1, b - 1  # 转换为0索引
                graph[a].append(b)  # a 应该在 b 之前
                indegree[b] += 1

            queue = []
            order = []

            # 找到所有入度为0的节点
            for i in range(k):
                if indegree[i] == 0:
                    queue.append(i)

            # 拓扑排序
            while queue:
                node = queue.pop(0)
                order.append(node)

                for neighbor in graph[node]:
                    indegree[neighbor] -= 1
                    if indegree[neighbor] == 0:
                        queue.append(neighbor)

            # 如果无法排序所有节点，说明有环
            if len(order) != k:
                return None

            return order

        # 获取行和列的拓扑排序
        row_order = topological_sort(rowConditions)
        col_order = topological_sort(colConditions)

        if row_order is None or col_order is None:
            return []

        # 创建位置映射：元素 -> 在该维度中的位置
        row_pos = {}
        col_pos = {}

        for i, num in enumerate(row_order):
            row_pos[num] = i

        for i, num in enumerate(col_order):
            col_pos[num] = i

        # 构建结果矩阵
        ans = [[0] * k for _ in range(k)]

        for num in range(k):
            row = row_pos[num]
            col = col_pos[num]
            ans[row][col] = num + 1  # 转换回1索引
            
        return ans
