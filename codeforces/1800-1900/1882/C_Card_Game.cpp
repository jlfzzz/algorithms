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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    int ans = 0;
    for (int i = 3; i <= n; i++) {
        if (a[i] > 0) {
            ans += a[i];
        }
    }

    if (n > 1) {
        if (a[1] >= 0) {
            ans += a[1];
            if (a[2] >= 0) {
                ans += a[2];
            }
        } else {
            if (a[1] + a[2] > 0) {
                ans += a[1] + a[2];
            }
        }
    } else {
        if (a[1] > 0) {
            ans += a[1];
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
