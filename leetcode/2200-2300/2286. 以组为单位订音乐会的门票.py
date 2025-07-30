import sys
import math
import bisect
import heapq
import collections
import functools
import itertools
import threading
from typing import List


class Node:
    def __init__(self) -> None:
        self.mx = 0
        self.seats = 0


class SegmentTree:
    def __init__(self, n: int, m: int) -> None:
        self.tree = [Node() for _ in range(2 << (n - 1).bit_length())]
        self.m = m
        self.build(1, 0, n - 1)

    def maintain(self, o: int):
        self.tree[o].mx = max(self.tree[o * 2].mx, self.tree[o * 2 + 1].mx)
        self.tree[o].seats = self.tree[o * 2].seats + self.tree[o * 2 + 1].seats

    def build(self, o: int, l: int, r: int) -> None:
        if l == r:
            self.tree[o].mx = self.m
            self.tree[o].seats = self.m
            return
        m = (l + r) // 2
        self.build(o * 2, l, m)
        self.build(o * 2 + 1, m + 1, r)
        self.maintain(o)

    def update(self, o: int, l: int, r: int, index: int, taken: int):
        if l == r:
            self.tree[o].mx -= taken
            self.tree[o].seats -= taken
            return
        m = (l + r) // 2
        if index <= m:
            self.update(o * 2, l, m, index, taken)
        else:
            self.update(o * 2 + 1, m + 1, r, index, taken)
        self.maintain(o)

    def find_first(self, o: int, l: int, r: int, L: int, R: int, need: int):
        if self.tree[o].mx < need:
            return [-1, -1]

        if l == r:
            return [l, self.tree[o].seats]

        m = (l + r) // 2

        lst = [-1, -1]
        if L <= m:
            lst = self.find_first(o * 2, l, m, L, R, need)
        if lst[0] < 0 and R > m:
            lst = self.find_first(o * 2 + 1, m + 1, r, L, R, need)
        return lst

    def query(self, o: int, l: int, r: int, L: int, R: int):
        if l >= L and r <= R:
            return self.tree[o].seats

        if l == r:
            return self.tree[o].seats
        m = (l + r) // 2
        res = 0
        if m >= L:
            res += self.query(o * 2, l, m, L, R)
        if R > m:
            res += self.query(o * 2 + 1, m + 1, r, L, R)
        return res


class BookMyShow:
    def __init__(self, n: int, m: int):
        self.st = SegmentTree(n, m)
        self.n = n
        self.m = m

    def gather(self, k: int, maxRow: int) -> List[int]:
        lst = self.st.find_first(1, 0, self.n - 1, 0, maxRow, k)
        if lst[0] < 0:
            return []
        self.st.update(1, 0, self.n - 1, lst[0], k)
        return [lst[0], self.m - lst[1]]

    def scatter(self, k: int, maxRow: int) -> bool:
        total = self.st.query(1, 0, self.n - 1, 0, maxRow)
        if total < k:
            return False

        i = 0
        while k > 0 and i <= maxRow:
            # 用 find_first 跳过没有空座的行
            lst = self.st.find_first(1, 0, self.n - 1, i, maxRow, 1)
            row = lst[0]
            if row == -1:
                break  # 没有更多座位了
            seats = lst[1]
            taken = min(k, seats)
            self.st.update(1, 0, self.n - 1, row, taken)
            k -= taken
            i = row + 1  # 继续处理下一行
        return True


class BookMyShow:

    def __init__(self, n: int, m: int):
        self.n = n
        self.m = m
        self.tree_sum = [0] * 4 * n
        self.mn = [0] * 4 * n

    def update(self, o: int, l: int, r: int, target: int, val: int) -> None:
        if l == r:
            self.tree_sum[o] += val
            self.mn[o] += val
            return

        mid = (l + r) // 2
        if target <= mid:
            self.update(o * 2, l, mid, target, val)
        else:
            self.update(o * 2 + 1, mid + 1, r, target, val)

        self.mn[o] = min(self.mn[o * 2], self.mn[o * 2 + 1])
        self.tree_sum[o] = self.tree_sum[o * 2] + self.tree_sum[o * 2 + 1]

    def query_sum(self, o: int, l: int, r: int, L: int, R: int) -> int:
        if L <= l and R >= r:
            return self.tree_sum[o]

        mid = (l + r) // 2
        res = 0
        if L <= mid:
            res += self.query_sum(o * 2, l, mid, L, R)
        if R > mid:
            res += self.query_sum(o * 2 + 1, mid + 1, r, L, R)
        return res

    def find_first(self, o: int, l: int, r: int, max_r: int, val: int):
        if self.mn[o] > val:
            return -1

        if l == r:
            return l

        mid = (l + r) // 2
        if self.mn[o * 2] <= val:
            return self.find_first(o * 2, l, mid, max_r, val)
        if max_r > mid:
            return self.find_first(o * 2 + 1, mid + 1, r, max_r, val)
        return -1

    def gather(self, k: int, maxRow: int) -> List[int]:
        row = self.find_first(1, 0, self.n - 1, maxRow, self.m - k)
        if row < 0:
            return []

        prev_cnt = self.query_sum(1, 0, self.n - 1, row, row)
        self.update(1, 0, self.n - 1, row, k)
        return [row, prev_cnt]

    def scatter(self, k: int, maxRow: int) -> bool:
        s = self.query_sum(1, 0, self.n - 1, 0, maxRow)
        if s > self.m * (maxRow + 1) - k:
            return False

        idx = self.find_first(1, 0, self.n - 1, maxRow, self.m - 1)
        while k:
            left = min(self.m - self.query_sum(1, 0, self.n - 1, idx, idx), k)
            self.update(1, 0, self.n - 1, idx, left)
            k -= left
            idx += 1
        return True


# Your BookMyShow object will be instantiated and called as such:
# obj = BookMyShow(n, m)
# param_1 = obj.gather(k, maxRow)
# param_2 = obj.scatter(k, maxRow)


class BookMyShow:
    def update(self, o: int, l: int, r: int, target: int, val: int) -> None:
        if l == r:
            self.tree_sum[o] += val
            self.mn[o] = self.tree_sum[o]
            self.row_[l] = self.tree_sum[o]
            return

        mid = (l + r) // 2
        if target <= mid:
            self.update(o * 2, l, mid, target, val)
        else:
            self.update(o * 2 + 1, mid + 1, r, target, val)
        self.mn[o] = min(self.mn[o * 2], self.mn[o * 2 + 1])
        self.tree_sum[o] = self.tree_sum[o * 2] + self.tree_sum[o * 2 + 1]

    def query_sum(self, o: int, l: int, r: int, L: int, R: int) -> int:
        if L <= l and R >= r:
            return self.tree_sum[o]

        mid = (l + r) // 2
        res = 0
        if L <= mid:
            res += self.query_sum(o * 2, l, mid, L, R)
        if R > mid:
            res += self.query_sum(o * 2 + 1, mid + 1, r, L, R)
        return res

    def find_first(self, o: int, l: int, r: int, R: int, min_taken: int) -> int:
        if self.mn[o] > min_taken:
            return -1

        if l == r:
            return l

        mid = (l + r) // 2
        if self.mn[o * 2] <= min_taken:
            return self.find_first(o * 2, l, mid, R, min_taken)
        if R > mid:
            return self.find_first(o * 2 + 1, mid + 1, r, R, min_taken)
        return -1

    def __init__(self, n: int, m: int):
        self.n = n
        self.m = m
        self.tree_sum = [0] * 4 * n
        self.mn = [0] * 4 * n
        self.row_ = [0] * n

    def gather(self, k: int, maxRow: int) -> List[int]:
        res = self.find_first(1, 0, self.n - 1, maxRow, self.m - k)
        if res < 0:
            return []
        temp = self.row_[res]
        self.update(1, 0, self.n - 1, res, k)
        return [res, temp]

    def scatter(self, k: int, maxRow: int) -> bool:
        total = self.query_sum(1, 0, self.n - 1, 0, maxRow)
        if (maxRow + 1) * self.m - total < k:
            return False

        first_row = self.find_first(1, 0, self.n - 1, maxRow, self.m - 1)
        # k -= self.m - self.row_[first_row]
        while k > 0:
            temp = self.row_[first_row]
            self.update(1, 0, self.n - 1, first_row, min(k, self.m - temp))
            k -= self.m - temp
            first_row += 1
        return True
