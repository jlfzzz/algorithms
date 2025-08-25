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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    vector<int> c(n);
    For(i, n) cin >> c[i];

    vector<pii> b(n);
    For(i, n) b[i] = {a[i], c[i]};

    ranges::sort(b);

    int ans = 0;

    for (int i = 0; i < n; i++) {
        int x = b[i].first, cx = b[i].second;

        int k1 = min(cx, m / x);
        int coins = m - k1 * x;
        int k2 = 0;

        if (i + 1 < n && b[i + 1].first == x + 1) {
            int cx1 = b[i + 1].second;
            k2 = min(cx1, coins / (x + 1));

            int r = min({k1, cx1 - k2, coins - k2 * (x + 1)});
            if (r < 0)
                r = 0;
            ans = max(ans, (k1 - r) * x + (k2 + r) * (x + 1));
        } else {
            ans = max(ans, k1 * x);
        }
    }

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
