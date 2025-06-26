class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        n, m = len(s), k.bit_length()
        if n < m:  # int(s, 2) < k
            return n  # 全选
        ans = m if int(s[-m:], 2) <= k else m - 1  # 后缀长度
        return ans + s[:-m].count("0")  # 添加前导零


class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        cur_bit = 1
        cur = 0
        n = len(s)
        res = 0
        for i in range(n - 1, -1, -1):
            if s[i] == "0":
                res += 1
            else:
                if cur + cur_bit <= k:
                    res += 1
                    cur += cur_bit
            cur_bit *= 2
        return res


class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        n = len(s)
        inf = 10**9 + 1
        dp = [inf] * (1 + n)
        dp[0] = 0
        for i in range(n):  # 第i+1个数
            for j in range(i, -1, -1):
                dp[j + 1] = min(dp[j + 1], dp[j] * 2 + int(s[i]))
        for i in range(n, 0, -1):
            if dp[i] <= k:
                return i
        return 0
