#include <algorithm>
#include <cstdio>

using ll = long long;

const int N = 2e5 + 2;
int T, n, a[N];
ll pre[N], suf[N], ans = 0;

signed main() {
    for (scanf("%d", &T); T--;) {
        scanf("%d", &n);
        pre[n + 1] = suf[n + 1] = 0;
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for (int i = 1; i <= n; ++i)
            pre[i] = pre[i - 1] + (a[i] > 0 ? a[i] : 0);
        for (int i = n; i; --i)
            suf[i] = suf[i + 1] + (a[i] < 0 ? -a[i] : 0);
        ans = 0;
        for (int i = 1; i <= n; ++i)
            ans = std::max(ans, pre[i] + suf[i]);
        printf("%lld\n", ans);
    }
    return 0;
}
