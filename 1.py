class BookMyShow:

    def __init__(self, n: int, m: int):
        self.sum = [0] * (4 * n)
    

    def add(self, o: int, l: int, r: int, idx: int, val: int):
        if l == r:
            self.sum[l] += val
            return

        mid = (l + r) // 2 
        if idx <= mid:
            self.add(o * 2, l, mid, idx, val)
        else:
            self.add(o * 2 + 1, mid + 1, r, idx, val)
        self.sum[o] = self.sum[o * 2] + self.sum[o * 2 + 1]

    def query_sum(self, o: int, l: int, r: int, L: int, R:int):
        if L <= l and r <= R:
            return self.sum[o]
        sum = 0
        mid = (l + r) // 2
        if L <= mid:
            sum += self.query_sum(o * 2, l, mid, L, R)
        if R > mid:
            sum += self.query_sum(o * 2 + 1, mid + 1, r, L, R)
        return sum


