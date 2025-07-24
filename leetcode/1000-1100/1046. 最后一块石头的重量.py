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
MOD = int(1e9 + 7)


class Solution:
    def lastStoneWeight(self, stones: List[int]) -> int:
        # 初始化
        heap = [-stone for stone in stones]
        heapify(heap)

        # 模拟
        while len(heap) > 1:
            x, y = heappop(heap), heappop(heap)
            if x != y:
                heappush(heap, x - y)

        if heap:
            return -heap[0]
        return 0
