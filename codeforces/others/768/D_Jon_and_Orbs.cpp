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
    int k, q;
    cin >> k >> q;

    int N = 10000;
    vector<vector<double>> dp(N + 1, vector<double>(k + 1));
    dp[1][1] = 1;

    for (int i = 2; i <= N; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = dp[i - 1][j] * ((double) j / k);
            if (j - 1 >= 1) {
                dp[i][j] += dp[i - 1][j - 1] * ((double) (k - j + 1) / k);
            }
        }
    }

    vector<double> temp;
    for (int i = 0; i <= N; i++) {
        temp.push_back(dp[i][k]);
    }

    while (q--) {
        int p;
        cin >> p;

        double prob = (double) p / 2000;
        int i = ranges::lower_bound(temp, prob) - temp.begin();

        cout << i << '\n';
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
