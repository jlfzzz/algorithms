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

"""
lc 3241
"""
class Solution:
    def timeTaken(self, edges: List[List[int]]) -> List[int]:
        g = [[] for _ in range(len(edges) + 1)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # nodes[x] 保存子树 x 的最大深度 max_d，次大深度 max_d2，以及最大深度要往儿子 my 走
        nodes = [None] * len(g)

        def dfs(x: int, fa: int) -> int:
            max_d = max_d2 = my = 0
            for y in g[x]:
                if y == fa:
                    continue
                depth = dfs(y, x) + 2 - y % 2  # 从 x 出发，往 my 方向的最大深度
                if depth > max_d:
                    max_d2 = max_d
                    max_d = depth
                    my = y
                elif depth > max_d2:
                    max_d2 = depth
            nodes[x] = (max_d, max_d2, my)
            return max_d

        dfs(0, -1)

        ans = [0] * len(g)

        def reroot(x: int, fa: int, from_up: int) -> None:
            max_d, max_d2, my = nodes[x]
            ans[x] = max(from_up, max_d)
            w = 2 - x % 2  # 从 y 到 x 的边权
            for y in g[x]:
                if y != fa:
                    reroot(y, x, max(from_up, max_d2 if y == my else max_d) + w)

        reroot(0, -1, 0)
        return ans


"""
lc q834 树中距离之和，边权都是1
先求根0到所有点的距离之和，并维护途中路径上所有节点的到它们的所有儿子的距离之和
再维护一个数组记录每个点包含的所有节点数（路径的所有儿子）
从0开始，dp[next] = dp[i] - cnt_node[next] + (n - cnt_node[next])
从上一个节点转移，先减去自己的所有儿子的数目再加上一个节点所有数目
"""


class Solution:
    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:
        g = [[] for _ in range(n)]  # g[x] 表示 x 的所有邻居
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        ans = [0] * n
        size = [1] * n  # 注意这里初始化成 1 了，下面只需要累加儿子的子树大小

        def dfs(x: int, fa: int, depth: int) -> None:
            ans[0] += depth  # depth 为 0 到 x 的距离
            for y in g[x]:  # 遍历 x 的邻居 y
                if y != fa:  # 避免访问父节点
                    dfs(y, x, depth + 1)  # x 是 y 的父节点
                    size[x] += size[y]  # 累加 x 的儿子 y 的子树大小

        dfs(0, -1, 0)  # 0 没有父节点

        def reroot(x: int, fa: int) -> None:
            for y in g[x]:  # 遍历 x 的邻居 y
                if y != fa:  # 避免访问父节点
                    ans[y] = ans[x] + n - 2 * size[y]
                    reroot(y, x)  # x 是 y 的父节点

        reroot(0, -1)  # 0 没有父节点
        return ans


"""
lc q310 树中最小高度
第一个dfs从根节点0开始，存储每个节点的第一，二深的节点信息
第二个dfs进行转移，判断儿子是不是来自这个第一深的节点
是的话，就用第二深的加1去更新，否则都用第一深的加1去更新
（此题用拓扑更简单）
"""


class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if n == 1:
            return [0]

        # 构建无向图
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # max_2[i] 表示从节点 i 往下走的前两个最长路径和其来源节点
        max_2 = [[(0, -1), (0, -1)] for _ in range(n)]

        # 第一次 DFS：从下往上计算每个节点的前两大子树路径长度
        def dfs1(i: int, fa: int) -> Tuple[int, int]:
            res = [(0, -1), (0, -1)]
            for v in g[i]:
                if v == fa:
                    continue
                (child_max_len, _) = dfs1(v, i)
                current_len = child_max_len + 1
                if current_len > res[0][0]:
                    res[1] = res[0]
                    res[0] = (current_len, v)
                elif current_len > res[1][0]:
                    res[1] = (current_len, v)
            max_2[i] = res[:]
            return res[0]  # 返回最长路径

        dfs1(0, -1)

        # 第二次 DFS：换根，从父亲传来的路径往子节点传播
        ans_len = inf
        ans = []

        def dfs2(i: int, fa: int):
            nonlocal ans_len, ans

            mx1, from1 = max_2[i][0]
            mx2, from2 = max_2[i][1]

            # 更新答案
            if mx1 < ans_len:
                ans_len = mx1
                ans = [i]
            elif mx1 == ans_len:
                ans.append(i)

            # 向子节点传递信息（换根）
            for v in g[i]:
                if v == fa:
                    continue

                # 如果 v 是从 max_2[i][0] 这条最长路径来的
                if v == from1:
                    propagated = mx2 + 1
                else:
                    propagated = mx1 + 1

                # 尝试更新 max_2[v] 来自父亲的路径
                if propagated > max_2[v][0][0]:
                    max_2[v][1], max_2[v][0] = max_2[v][0], (propagated, i)
                elif propagated > max_2[v][1][0]:
                    max_2[v][1] = (propagated, i)

                dfs2(v, i)

        dfs2(0, -1)
        return ans
