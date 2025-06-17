class Solution:
    def minMaxDifference(self, num: int) -> int:
        s = str(num)
        mx = num
        for c in s:
            if c != "9":  # 第一个不等于 9 的字符
                mx = int(s.replace(c, "9"))  # 替换成 9
                break
        mn = int(s.replace(s[0], "0"))  # 第一个不等于 0 的字符，替换成 0
        return mx - mn
