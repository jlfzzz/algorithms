class Solution:
    def maximum69Number(self, num: int) -> int:
        max_base = 0
        base = 1
        x = num
        while x:
            x, d = divmod(x, 10)
            if d == 6:
                max_base = base
            base *= 10
        return num + max_base * 3
