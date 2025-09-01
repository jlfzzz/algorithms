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
    int have = 0;
    For(i, k) {
        int r, c;
        cin >> r >> c;
        if (r == c) {
            have++;
        } else {
            have += 2;
        }
    }

    int rem = n - have;
    vector<int> dp(rem + 1);
    dp[0] = 1;
    for (int i = 1; i <= rem; i++) {
        dp[i] = dp[i - 1];
        if (i - 2 >= 0) {
            dp[i] = (dp[i] + (dp[i - 2] * (2 * (n - 1 - have - i + 2) % MOD) % MOD)) % MOD;
        }
    }

    cout << dp[rem] << '\n';
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
