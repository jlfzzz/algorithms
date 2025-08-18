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
    int n;
    cin >> n;

    vector<int> r(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }

    int ans = 0;
    vector<int> in(n + 1);
    for (int i = 1; i <= n; i++) {
        in[r[i]]++;
    }

    deque<int> dq;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0)
            dq.push_back(i);
    }

    vector<bool> vis(n + 1);
    vector<int> dp(n + 1);

    while (!dq.empty()) {
        int x = dq.front();
        dq.pop_front();

        int target = r[x];
        // if (!vis[target]) {
        //     dp[target] = dp[x] + 1;
        //     vis[target] = true;
        // }
        dp[target] = max(dp[x] + 1, dp[target]);

        ans = max(ans, dp[target]);
        in[target]--;
        if (in[target] == 0) {
            dq.push_back(target);
        }
    }
    cout << ans + 2 << '\n';
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
