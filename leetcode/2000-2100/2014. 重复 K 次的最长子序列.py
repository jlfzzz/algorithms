from itertools import permutations
from typing import Counter


class Solution:
    def longestSubsequenceRepeatedK(self, s: str, k: int) -> str:
        num = Counter(s)
        hot = "".join(ele * (num[ele] // k) for ele in sorted(num, reverse=True))
        for i in range(len(hot), 0, -1):
            for item in permutations(hot, i):
                word = "".join(item)
                ss = iter(s)
                if all(c in ss for c in word * k):
                    return word
        return ""
