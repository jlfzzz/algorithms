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

    vector<int> v{1, 3, 6, 10, 15};
    vector<int> dp(2000, inf);
    dp[0] = 0;

    for (int x: v) {
        for (int i = x; i < 2000; i++) {
            dp[i] = min(dp[i], dp[i - x] + 1);
        }
    }

    int d = n - 500;
    int ans = 0;
    if (d > 0) {
        ans += (d + 14) / 15;
        n -= ans * 15;
    }

    // cout << n << '\n';
    ans += dp[n];

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
