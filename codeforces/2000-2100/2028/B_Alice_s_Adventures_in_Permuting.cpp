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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, b, c;
    cin >> n >> b >> c;

    // if (b == 0 && c == 0) {
    //     cout << -1 << '\n';
    //     return;
    // }

    if (b == 0) {
        if (n - c > 2) {
            cout << -1 << '\n';
            return;
        }
    }

    int lo = 0, hi = n;
    int mx = n;
    if (b == 0 && c < n) {
        mx = 1;
    }
    while (lo < hi) {
        int m = lo + (hi - lo) / 2;
        __int128 t = (__int128) b * m + c;
        if (t >= n) {
            hi = m;
            mx = m;
        } else {
            lo = m + 1;
        }
    }

    // cout << "mx is : " << mx << endl;

    cout << n - mx << '\n';
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
