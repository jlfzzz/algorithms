class Solution:
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:
        ans = []
        n = len(s)

        mn_len = n + 1
        left = 0
        cnt = 0
        for i, c in enumerate(s):
            cnt += ord(c) & 1
            if cnt == k:
                while s[left] == "0":
                    left += 1
                if i - left + 1 < mn_len:
                    ans.clear()
                    mn_len = i - left + 1
                    ans.append(s[left : i + 1])
                elif i - left + 1 == mn_len:
                    ans.append(s[left : i + 1])
                cnt -= 1
                left += 1
        return min(ans) if len(ans) != 0 else ""


class Solution:
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:
        if s.count("1") < k:
            return ""
        ans = s
        cnt1 = left = 0
        for right, c in enumerate(s):
            cnt1 += int(c)
            while cnt1 > k or s[left] == "0":
                cnt1 -= int(s[left])
                left += 1
            if cnt1 == k:
                t = s[left : right + 1]
                if len(t) < len(ans) or len(t) == len(ans) and t < ans:
                    ans = t
        return ans
