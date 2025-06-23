ans = [[] for _ in range(10)]


def is_p(x: int, k: int) -> bool:
    if x % k == 0:
        return False

    s = 0
    while s < x // k:
        s = s * k + x % k
        x //= k
    return s == x or s == x // k


def is_done(x: int) -> bool:
    ret = True
    for i in range(2, 10):
        if len(ans[i]) >= 30:
            continue
        ret = False
        if is_p(x, i):
            ans[i].append(x)

    if not ret:
        return False

    for i in range(2, 10):
        s = 0
        for j in range(30):
            s += ans[i][j]
            ans[i][j] = s

    return True


def init() -> None:
    base = 1
    while True:
        for i in range(base, base * 10):
            x = i
            t = x // 10
            while t > 0:
                x = x * 10 + t % 10
                t //= 10
            if is_done(x):
                return

        for i in range(base, base * 10):
            x = i
            t = x
            while t > 0:
                x = x * 10 + t % 10
                t //= 10
            if is_done(x):
                return

        base = base * 10

# init必须在外面call 不然是错的，因为可能答案被覆盖了
init()


class Solution:
    def kMirror(self, k: int, n: int) -> int:

        return ans[k][n - 1]
