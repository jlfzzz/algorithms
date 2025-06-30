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
    def findLHS(self, nums: List[int]) -> int:
        cnt = defaultdict(int)
        n = len(nums)
        ans = 0
        for i in range(n - 1, -1, -1):
            x = nums[i]
            cnt[x] += 1
            t1 = cnt[x] + cnt[x + 1] if cnt[x + 1] != 0 else 0
            t2 = cnt[x] + cnt[x - 1] if cnt[x - 1] != 0 else 0
            ans = max(ans, t1, t2)

        return ans
