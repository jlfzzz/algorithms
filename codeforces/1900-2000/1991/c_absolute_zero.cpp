#include <algorithm>
#include <cstdio>
const int maxn = 2e5;
int T, n, tot, a[maxn + 1], b[maxn + 1];
bool flag;
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        flag = true;
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        while (true) {
            int maxx = 0, minx = a[1], mid;
            for (int i = 1; i <= n; ++i) {
                maxx = std::max(maxx, a[i]);
                minx = std::min(minx, a[i]);
            }
            mid = (maxx + minx + 1) / 2;
            if (!mid || (maxx == 1 && minx == 0)) {
                break;
            }
            b[++tot] = mid;
            for (int i = 1; i <= n; ++i) {
                a[i] = std::abs(a[i] - mid);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (a[i]) {
                flag = false;
                break;
            }
        }
        if (!flag) {
            puts("-1");
        } else {
            printf("%d\n", tot);
            for (int i = 1; i <= tot; ++i) {
                printf("%d ", b[i]);
            }
            puts("");
        }
    }
    return 0;
}
