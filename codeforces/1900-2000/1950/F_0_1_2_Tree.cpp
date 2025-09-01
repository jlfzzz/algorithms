#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    int ans = -1;
    if (c != a + 1) {
        cout << -1 << '\n';
        return;
    }
    int ra = a, rb = b, rc = c;
    int cur = 1;
    int h = 0;
    while (cur > 0) {
        int x = min(cur, ra);
        ra -= x;
        int left = cur - x;
        int y = min(left, rb);
        rb -= y;
        int z = left - y;
        rc -= z;
        h += 1;
        cur = 2 * x + y;
    }
    if (ra == 0 && rb == 0 && rc == 0)
        ans = h - 1;
    else
        ans = -1;
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
