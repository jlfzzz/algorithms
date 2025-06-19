class Solution:
    def divisorSubstrings(self, num: int, k: int) -> int:
        s = str(num)
        ans = 0
        n = len(s)

        for i in range(n - k + 1):
            j = int(s[i : i + k])
            if j != 0 and num % j == 0:
                ans += 1
        return ans
