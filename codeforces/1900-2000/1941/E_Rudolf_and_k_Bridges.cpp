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
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<int> cost(n);
    For(i, n) {
        vector<int> temp(m);
        For(j, m) cin >> temp[j];

        vector<int> dp(m, inf);
        dp[0] = 1;
        set<pii> pre;
        pre.insert({1, 0});
        for (int j = 1; j < m; j++) {
            auto &[c, idx] = *pre.begin();
            dp[j] = c + temp[j] + 1;
            pre.insert({dp[j], j});
            if (j - d - 1 >= 0) {
                int L = j - d - 1;
                pii p{dp[L], L};
                pre.erase(p);
            }
        }
        cost[i] = dp.back();
    }

    int ans = inf;
    int l = 0;
    int window = 0;
    for (int r = 0; r < n; r++) {
        window += cost[r];
        if (r - l + 1 == k) {
            ans = min(ans, window);
            window -= cost[l];
            l++;
        }
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
