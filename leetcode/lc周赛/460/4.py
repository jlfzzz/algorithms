from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        n = len(nums)
        all_xors = [0] * (1 << n)
        for mask in range(1 << n):
            t = 0
            for j in range(n):
                if mask >> j & 1:
                    t ^= nums[j]
            all_xors[mask] = t

        all_ands = [0] * (1 << n)
        for mask in range(1 << n):
            if mask == 0:
                all_ands[mask] = 0 
                continue

            t = nums[0] if mask & 1 else float("inf")
            for j in range(n):
                if mask >> j & 1:
                    if t == float("inf"):
                        t = nums[j]
                    else:
                        t &= nums[j]
            all_ands[mask] = t if t != float("inf") else 0

        ans = 0
        for maskA in range(1 << n):
            for maskB in range(1 << n):
                # 检查A和B是否有重叠
                if maskA & maskB != 0:
                    continue

                # C的mask是剩余的元素
                maskC = ((1 << n) - 1) ^ maskA ^ maskB

                # 计算XOR(A) + AND(B) + XOR(C)
                xor_A = all_xors[maskA]
                and_B = all_ands[maskB]
                xor_C = all_xors[maskC]

                result = xor_A + and_B + xor_C
                max_result = max(max_result, result)
