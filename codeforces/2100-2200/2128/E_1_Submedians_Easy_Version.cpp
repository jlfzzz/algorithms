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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int mx = ranges::max(a);
    int mn = ranges::min(a);

    int lo = mn, hi = mx + 1;
    int ans = -1;
    pii res{-1, -1};

    while (lo < hi) {
        int m = (lo + hi) / 2;

        auto check = [&](int median) -> pii {
            pii res = {-1, -1};
            vector<int> pre(n + 1);
            for (int i = 1; i <= n; i++) {
                pre[i] = pre[i - 1] + (a[i - 1] >= median ? 1 : -1);
            }

            pii mn{inf, 0};
            for (int i = k; i <= n; i++) {
                if (pre[i - k] < mn.first) {
                    mn = {pre[i - k], i - k};
                }
                if (pre[i] - mn.first >= 0) {
                    res = {mn.second, i};
                    break;
                }
            }
            return res;
        };

        auto [x, y] = check(m);
        if (x != -1 && y != -1) {
            ans = m;
            res = {x, y};
            lo = m + 1;
        } else {
            hi = m;
        }
    }

    cout << ans << ' ' << (res.first + 1) << ' ' << res.second << '\n';
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
