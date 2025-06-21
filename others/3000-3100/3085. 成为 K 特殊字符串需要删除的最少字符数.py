from collections import Counter
from math import inf


class Solution:
    def minimumDeletions(self, word: str, k: int) -> int:

        freq = Counter(word)

        values = sorted(list(freq.values()))
        ans = inf
        prefix = 0
        for i, mn in enumerate(values):
            curr = prefix
            prefix += mn
            for j in range(i + 1, len(values)):
                curr += max(0, values[j] - mn - k)
            ans = min(curr, ans)
        return ans
