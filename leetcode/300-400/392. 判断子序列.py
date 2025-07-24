class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        if not s:
            return True
        i = 0
        for c in t:
            if s[i] == c:
                i += 1
                if i == len(s):  # 所有字符匹配完毕
                    return True  # s 是 t 的子序列
        return False


class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        n = len(t)
        nxt = [[n] * 26 for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            nxt[i][:] = nxt[i + 1]
            nxt[i][ord(t[i]) - ord("a")] = i

        # 这个写法无论 s 为空还是 t 为空，都能算出正确答案
        i = -1
        for c in s:
            i = nxt[i + 1][ord(c) - ord("a")]
            if i == n:  # c 不在 t 中，说明 s 不是 t 的子序列
                return False
        return True  # s 是 t 的子序列
