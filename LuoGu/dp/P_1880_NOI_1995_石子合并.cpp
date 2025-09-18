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

    a.insert(a.end(), a.begin(), a.end());
    vector<int> pre(2 * n + 1);
    vector<vector<int>> dp1(2 * n + 1, vector<int>(2 * n + 1));
    vector<vector<int>> dp2(2 * n + 1, vector<int>(2 * n + 1));


    for (int i = 0; i < 2 * n; i++) {
        pre[i + 1] = pre[i] + a[i];
        dp1[i][i] = dp2[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < 2 * n; l++) {
            int r = l + len - 1;
            dp1[l][r] = inf;
            dp2[l][r] = -inf;
            int sum = pre[r + 1] - pre[l];
            for (int k = l; k < r; k++) {
                dp1[l][r] = min(dp1[l][r], dp1[l][k] + dp1[k + 1][r] + sum);
                dp2[l][r] = max(dp2[l][r], dp2[l][k] + dp2[k + 1][r] + sum);
            }
        }
    }

    int ans_min = inf, ans_max = -inf;
    for (int l = 0; l < n; l++) {
        int r = l + n - 1;
        ans_min = min(ans_min, dp1[l][r]);
        ans_max = max(ans_max, dp2[l][r]);
    }

    cout << ans_min << "\n" << ans_max << "\n";
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
