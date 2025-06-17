class Solution:
    def myPow(self, x: float, n: int) -> float:
        return pow(x, n)


class Solution:
    def myPow(self, x: float, n: int) -> float:
        def f(x: float, n: int) -> float:
            m = n.bit_length()
            base = x
            ans = 1.0
            for i in range(m):
                if n >> i & 1:
                    ans *= base
                base *= base
            return ans

        return f(x, n) if n >= 0 else f(1 / x, -n)


class Solution:
    def myPow(self, x: float, n: int) -> float:
        def quickMul(N):
            if N == 0:
                return 1.0
            y = quickMul(N // 2)
            return y * y if N % 2 == 0 else y * y * x

        return quickMul(n) if n >= 0 else 1.0 / quickMul(-n)
