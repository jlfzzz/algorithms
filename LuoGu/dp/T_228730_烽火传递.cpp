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
    int n, m;
    cin >> n >> m;

    vector<int> cost(n + 1);
    For(i, n) cin >> cost[i + 1];

    vector<int> dp(n + 1, -inf);
    dp[0] = 0;

    deque<int> dq;
    dq.push_back(0);

    for (int i = 1; i <= n; i++) {
        while (!dq.empty() && i - dq.front() > m) {
            dq.pop_front();
        }

        int j = dq.front();
        dp[i] = dp[j] + cost[i];

        while (!dq.empty() && dp[i] <= dp[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }


    int ans = inf;
    for (int i = max(1LL, n - m + 1); i <= n; i++) {
        ans = min(ans, dp[i]);
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
