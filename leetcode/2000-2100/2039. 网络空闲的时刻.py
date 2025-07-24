from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def networkBecomesIdle(self, edges: List[List[int]], patience: List[int]) -> int:
        n = len(patience)
        graph = [[] for _ in range(n)]
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)
        vis = [False] * n
        vis[0] = True
        dis = [0] * n
        q = Queue()
        q.put((0, 0))
        while not q.empty():
            x, d = q.get()
            for v in graph[x]:
                if not vis[v]:
                    vis[v] = True
                    dis[v] = d + 1
                    q.put((v, d + 1))
        ans = 1
        for i in range(1, n):
            # 往返时间
            round_trip = 2 * dis[i]
            # 耐心值
            patience_val = patience[i]

            # 如果往返时间小于等于耐心值，只发送一次
            if round_trip <= patience_val:
                ans = max(ans, round_trip + 1)
            else:
                # 计算重发次数：在第一次消息返回前会发送多少次
                resend_count = (round_trip - 1) // patience_val
                # 最后一次发送的时间
                last_send_time = resend_count * patience_val
                # 最后一次消息返回的时间
                last_return_time = last_send_time + round_trip
                ans = max(ans, last_return_time + 1)

        return ans
