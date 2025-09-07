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

    int mn = min(a, c);
    if (b >= mn) {
        cout << mn << '\n';
    } else {
        int lo = 0, hi = 1e9 + 5;

        int ans = 0;
        while (lo < hi) {
            int m = lo + (hi - lo) / 2;

            if (m > a || m > c) {
                hi = m;
                continue;
            }

            int left = b + a - m + c - m;
            if (left >= m) {
                lo = m + 1;
                ans = m;
            } else {
                hi = m;
            }
        }

        cout << ans << '\n';
    }
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
