from math import *
from typing import List
from collections import *


class Solution:
    def maxTaskAssign(
        self, tasks: List[int], workers: List[int], pills: int, strength: int
    ) -> int:
        tasks.sort()
        workers.sort()
        n = len(tasks)
        m = len(workers)

        lo = 0
        hi = min(n, m) + 1
        ans = 0

        while lo < hi:
            mid = (lo + hi) // 2

            def check(target: int) -> bool:
                i = 0
                j = m - target
                dq = deque()
                used = 0
                while j < m:
                    while i < n and workers[j] + strength >= tasks[i]:
                        dq.append(tasks[i])
                        i += 1

                    if not dq:
                        return False

                    if dq[0] > workers[j] and used == pills:
                        return False

                    if dq[0] <= workers[j]:
                        dq.popleft()
                    else:
                        used += 1
                        dq.pop()
                    j += 1
                return True

            if check(mid):
                ans = mid
                lo = mid + 1
            else:
                hi = mid
        return ans
