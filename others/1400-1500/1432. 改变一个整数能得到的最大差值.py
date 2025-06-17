class Solution:
    def maxDiff(self, num: int) -> int:
        s = str(num)

        mx = num
        for d in s:
            if d != "9":
                mx = int(s.replace(d, "9"))
                break

        mn = num
        if s[0] != "1":
            mn = int(s.replace(s[0], "1"))
        else:
            for d in s:
                if d > "1":  # 不是 0 也不是 1
                    mn = int(s.replace(d, "0"))
                    break

        return mx - mn
