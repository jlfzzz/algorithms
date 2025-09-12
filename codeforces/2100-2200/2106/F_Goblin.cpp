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
    //cout << n << endl;
    string s;
    cin >> s;
    //cout << s << endl;

    vector<pii> dp(n + 1, {0, 0});
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        //cout << i << endl;
        if (s[i] == '0') {
            dp[i].first = dp[i + 1].first + i;
            dp[i].second = dp[i + 1].second + n - i - 1;
        } else {
            dp[i].first = 0;
            dp[i].second = dp[i + 1].first + 1;
        }
        ans = max({ans, dp[i].first, dp[i].second});
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
