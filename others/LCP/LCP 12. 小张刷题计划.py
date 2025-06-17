from typing import List
from bisect import *

class Solution:
    def minTime(self, time: List[int], m: int) -> int:
        l, r = 0, sum(time)
        while l < r:
            mid = (l + r) >> 1
            if self.check(mid, time, m):
                r = mid
            else:
                l = mid + 1
        return l

    def check(self, limit, cost, day):
        use_day, total_time, max_time = 1, 0, cost[0]
        for i in cost[1:]:
            if total_time + min(max_time, i) <= limit:
                total_time, max_time = total_time + min(max_time, i), max(max_time, i)
            else:
                use_day += 1
                total_time, max_time = 0, i
        return use_day <= day
