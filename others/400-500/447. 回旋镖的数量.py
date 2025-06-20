from typing import List
from collections import *


class Solution:
    def numberOfBoomerangs(self, points: List[List[int]]) -> int:
        ans = 0
        for x1, y1 in points:
            cnt = defaultdict(int)
            for x2, y2 in points:
                d2 = (x1 - x2) ** 2 + (y1 - y2) ** 2
                ans += cnt[d2] * 2
                cnt[d2] += 1
        return ans
