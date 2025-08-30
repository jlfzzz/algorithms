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
    string s;
    cin >> s;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<int> last(26, -1);

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int c = s[i - 1] - 'a';
        for (int j = 0; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];

            if (j > 0) {
                dp[i][j] += dp[i - 1][j - 1];

                // 去重处理
                if (last[c] != -1) {
                    dp[i][j] -= dp[last[c] - 1][j - 1];
                }
            }

            dp[i][j] = min(dp[i][j], (int) 1e13);
        }
        last[c] = i;
    }

    int ans = 0;
    for (int len = n; len >= 0; len--) {
        int count = min(k, dp[n][len]);
        ans += (n - len) * count;
        k -= count;
        if (k == 0)
            break;
    }

    if (k > 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
