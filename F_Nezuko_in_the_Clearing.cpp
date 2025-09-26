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
    int h, d;
    cin >> h >> d;

    int lo = 0, hi = d + 1;
    auto check = [&](ll f) {
        i128 m = d / (f + 1), len = d % (f + 1);
        i128 cost1 = (i128) (1 + m + 1) * (m + 1) / 2;
        i128 cost2 = (i128) (1 + m) * m / 2;
        i128 tot = cost1 * len + (f + 1 - len) * cost2;
        return tot < (i128) (h + f);
    };

    int ans = 0;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (check(mid)) {
            hi = mid;
            ans = mid;
        } else {
            lo = mid + 1;
        }
    }

    cout << ans + d << endl;
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
