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

constexpr int K = 1e12 + 5;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    vector<vector<int>> last(26, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        for (int len = n; len >= 1; len--) {
            int add = dp[len - 1];
            int val = dp[len] + add;
            if (last[c][len] > 0)
                val -= last[c][len];
            if (val < 0)
                val = 0;
            if (val > K)
                val = K;
            dp[len] = val;
            int la = add;
            if (la > K)
                la = K;
            last[c][len] = la;
        }
    }
    int need = k;
    int ans = 0;
    for (int len = n; len >= 0 && need > 0; len--) {
        int take = min(need, dp[len]);
        ans += take * (n - len);
        need -= take;
    }
    if (need > 0) {
        cout << -1 << '\n';
        return;
    }
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    //  cin >> T;
    while (T--)
        solve();
    return 0;
}
