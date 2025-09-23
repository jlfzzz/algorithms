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
    string s;
    cin >> n >> s;

    int ans = 0;
    s = ' ' + s;

    vector<int> dp(n + 1);

    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') {
            dp[i] = dp[max(0ll, i - 3)] + i;
        } else {
            dp[i] = dp[i - 1];
        }
    }

    ans = accumulate(dp.begin(), dp.end(), 0ll);
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
