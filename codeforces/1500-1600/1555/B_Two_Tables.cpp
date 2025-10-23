#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
// #define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int W, H;
    cin >> W >> H;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int w, h;
    cin >> w >> h;

    int c = x2 - x1, d = y2 - y1;

    if (w + c > W && h + d > H) {
        cout << -1 << '\n';
        return;
    }

    double ans = 1e18;

    if (w + c <= W) {
        ans = min(ans, max(0, w - x1) * 1.0);
        ans = min(ans, max(0, x2 - (W - w)) * 1.0);
    }

    if (h + d <= H) {
        ans = min(ans, max(0, h - y1) * 1.0);
        ans = min(ans, max(0, y2 - (H - h)) * 1.0);
    }

    cout << fixed << setprecision(9) << ans << '\n';
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
