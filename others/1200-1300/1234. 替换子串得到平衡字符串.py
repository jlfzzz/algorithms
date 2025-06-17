from cmath import inf
from typing import Counter


class Solution:
    def balancedString(self, s: str) -> int:
        m = len(s) // 4
        cnt = Counter(s)
        if len(cnt) == 4 and min(cnt.values()) == m:  # 已经符合要求啦
            return 0

        ans, left = inf, 0
        for right, c in enumerate(s):  # 枚举子串右端点
            cnt[c] -= 1
            while max(cnt.values()) <= m:
                ans = min(ans, right - left + 1)
                cnt[s[left]] += 1
                left += 1  # 缩小子串
        return ans
