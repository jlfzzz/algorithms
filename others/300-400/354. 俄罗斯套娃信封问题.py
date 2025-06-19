from typing import List
from bisect import *


class Solution:
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        envelopes = sorted(envelopes, key=lambda x: (x[0], -x[1]))

        ans = []
        for _, y in envelopes:
            i = bisect_left(ans, y)
            if i == len(ans):
                ans.append(y)
            else:
                ans[i] = y
        return len(ans)
