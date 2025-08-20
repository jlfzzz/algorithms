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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];
    vector<int> b(m + 1);
    For(i, m) cin >> b[i + 1];

    if (ranges::max(a) > ranges::max(b)) {
        cout << -1 << '\n';
        return;
    }

    vector<vector<pii>> dp(n + 1, vector<pii>(m + 1, {inf, 0}));
    for (int j = 0; j <= m; ++j)
        dp[0][j] = {inf, 0};
    dp[0][1] = {0, 1};
    vector<int> pre_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        pre_sum[i] = pre_sum[i - 1] + a[i];
    }
    pre_sum.push_back(inf);

    for (int i = 1; i <= n; i++) {
        int pre_min = inf;
        int pre_cnt = 0;
        for (int j = 1; j <= m; j++) {
            int k = ranges::upper_bound(pre_sum, pre_sum[i - 1] + b[j]) - pre_sum.begin() - 1;
            if (k < i)
                break;

            if (dp[i - 1][j].first == pre_min) {
                pre_cnt = (pre_cnt + dp[i - 1][j].second) % MOD;
            } else if (dp[i - 1][j].first < pre_min) {
                pre_min = dp[i - 1][j].first;
                pre_cnt = dp[i - 1][j].second % MOD;
            }

            for (int l = i; l <= k; l++) {
                if (pre_min + m - j < dp[l][j].first) {
                    dp[l][j] = {pre_min + m - j, pre_cnt % MOD};
                } else if (pre_min + m - j == dp[l][j].first) {
                    dp[l][j].second = (dp[l][j].second + pre_cnt) % MOD;
                }
            }
        }
    }

    int ans = inf;
    int ans_cnt = 0;

    for (auto &[cost, cnt]: dp[n]) {
        if (cost != inf && ans == cost) {
            ans_cnt = (ans_cnt + cnt) % MOD;
        } else if (cost != inf && cost < ans) {
            ans = cost, ans_cnt = cnt % MOD;
        }
    }

    if (ans == inf) {
        cout << -1 << '\n';
    } else {
        cout << ans << ' ' << (ans_cnt % MOD) << '\n';
    }
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
