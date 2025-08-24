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
    vector<int> a(n);
    For(i, n) cin >> a[i];
    int ans = 0;

    for (int i = 0; i < n / 2; i++) {
        if (a[i] != a[n - i - 1]) {
            int t1 = a[i], t2 = a[n - 1 - i];
            int mn1 = -1, mn2 = -1;
            for (int j = 0; j < 32; j++) {
                if (t1 == t2) {
                    mn1 = j;
                }
                t1 = t1 ^ (t1 >> 1);
            }
            t1 = a[i], t2 = a[n - 1 - i];
            for (int j = 0; j < 32; j++) {
                if (t2 == t1) {
                    mn2 = j;
                }
                t2 = t2 ^ (t2 >> 1);
            }
            if (mn1 == -1 && mn2 == -1) {
                cout << -1 << '\n';
                return;
            }
            ans += min(mn1, mn2);
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
