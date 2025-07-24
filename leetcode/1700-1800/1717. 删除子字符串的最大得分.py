class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        a, b = "a", "b"
        if x < y:
            x, y = y, x
            a, b = b, a
        ans = cnt1 = cnt2 = 0
        for c in s:
            if c == a:
                cnt1 += 1
            elif c == b:
                if cnt1:
                    ans += x
                    cnt1 -= 1
                else:
                    cnt2 += 1
            else:
                ans += min(cnt1, cnt2) * y
                cnt1 = cnt2 = 0
        ans += min(cnt1, cnt2) * y
        return ans


class Solution:
    def maximumGain(self, S: str, x: int, y: int) -> int:
        n = len(S)
        l = []

        a, b = "a", "b"
        if x < y:
            a, b = b, a
            x, y = y, x

        curr = ""
        i = 0
        while i < n:
            c = S[i]
            if c != "a" and c != "b":
                if curr:
                    l.append(curr)
                curr = ""
            else:
                curr += c
            i += 1

        if curr:
            l.append(curr)

        def f(s: str) -> int:
            score = 0
            st = []
            for c in s:
                if c == b and st and st[-1] == a:
                    st.pop()
                    score += x
                else:
                    st.append(c)

            st2 = []
            for c in st:
                if c == a and st2 and st2[-1] == b:
                    st2.pop()
                    score += y
                else:
                    st2.append(c)
            return score

        return sum(f(s) for s in l)
