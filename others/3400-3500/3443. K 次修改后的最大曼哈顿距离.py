from collections import *


class Solution:
    def maxDistance(self, s: str, k: int) -> int:
        mp = defaultdict(str)
        mp[0] = "N"
        mp[1] = "E"
        mp[2] = "S"
        mp[3] = "W"

        ans = 0
        for i in range(4):
            j = (i + 1) % 4
            cnt = 0
            use = 0
            for c in s:
                if c == mp[i] or c == mp[j]:
                    cnt += 1
                else:
                    if use < k:
                        use += 1
                        cnt += 1
                    else:
                        cnt -= 1
                ans = max(ans, cnt)
        return ans
