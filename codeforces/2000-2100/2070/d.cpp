#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1, vector<int>());
    vector<int> parent(n + 1);
    For(i, n - 1) {
        int p;
        cin >> p;
        int child = i + 2;
        graph[p].push_back(child);
        parent[child] = p;
    }

    vector<int> dis(n + 1);
    auto dfs = [&](this auto &&dfs, int i, int d) -> void {
        dis[i] = d;
        for (int v: graph[i]) {
            dfs(v, d + 1);
        }
    };
    dfs(1, 0);
    int mx_d = ranges::max(dis);
    vector<int> dp(n + 1, 0);
    vector layers(mx_d + 1, vector<int>());
    for (int i = 1; i <= n; i++) {
        layers[dis[i]].push_back(i);
    }
    int sum = 0;
    for (int x: layers[1]) {
        dp[x] = 1;
        sum += 1;
    }
    dp[1] = 1;
    for (int i = 2; i <= mx_d; i++) {
        auto &layer = layers[i];
        int nxt_sum = 0;
        for (int x: layer) {
            dp[x] = (sum - dp[parent[x]] + MOD) % MOD;
            nxt_sum = (nxt_sum + dp[x]) % MOD;
        }
        sum = nxt_sum;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + dp[i]) % MOD;
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
