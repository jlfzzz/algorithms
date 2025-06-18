class Solution:
    def countPalindromicSubsequence(self, s: str) -> int:
        res = 0
        for ch in map(chr, range(97, 123)):  # 'a' to 'z'
            l = s.find(ch)
            r = s.rfind(ch)
            if l != -1 and r - l > 1:
                middle = set(s[l + 1 : r])
                res += len(middle)
        return res
