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
