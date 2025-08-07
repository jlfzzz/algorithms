#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    vector<vector<int>> g(n + 1, vector<int>());
    For(i, n - 1) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(2));
    dp[1][0] = a[1];
    dp[1][1] = a[1];

    auto dfs = [&](this auto &&dfs, int i, int fa) -> void {
        for (int v: g[i]) {
            if (v == fa)
                continue;

            ll curr = a[v];
            dp[v][0] = max(curr, -dp[i][1] + curr);
            dp[v][1] = min(curr, -dp[i][0] + curr);
            dfs(v, i);
        }
    };
    dfs(1, -1);

    for (int i = 1; i <= n; i++) {
        cout << dp[i][0] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
