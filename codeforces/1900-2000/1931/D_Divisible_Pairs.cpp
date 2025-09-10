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
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n);
    map<pii, int> cnt;
    For(i, n) cin >> a[i];

    int ans = 0;
    for (int i = 0; i < n; i++) {
        pii p = {a[i] % x, a[i] % y};
        if (p.first == 0) {
            if (cnt.contains({0, p.second})) {
                ans += cnt[{0, p.second}];
            }
            cnt[{0, p.second}]++;
        } else {
            if (cnt.contains({x - p.first, p.second})) {
                ans += cnt[{x - p.first, p.second}];
            }
            cnt[{p.first, p.second}]++;
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
