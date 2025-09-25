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
    int mx = 0;
    int ans = 0;
    int sum = 0;
    int d = inf;

    for (int i = 0; i < n; i++) {
        sum += a[i];
        mx = max(mx, sum);

        if (sum - mx < d) {
            d = sum - mx;
            ans = mx;
        }
    }

    // int t = 0;
    // for (int i = 0; i < n; i++) {
    //     if (a[i] >= 0) {
    //         t += a[i];
    //     } else {
    //         t = max(t + a[i], ans);
    //     }
    // }

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
