from typing import List


class Solution:
    def divideString(self, s: str, k: int, fill: str) -> List[str]:
        n = len(s)
        ans = []
        for i in range(0, n, k):
            ans.append(s[i : min(n, i + k)])
        if n % k == 0:
            return ans
        ans[-1] += fill * (k - n % k)
        return ans
