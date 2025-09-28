#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<int> weights(n + 1);
    For(i, n) { cin >> weights[i + 1]; }

    For(i, m) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int ans = 0;

    for (int v = 1; v <= n; v++) {
        int deg = graph[v].size();
        if (deg < 2)
            continue;

        for (int bit = 0; bit < 31; bit++) {
            int cnt0 = 0, cnt1 = 0;

            for (int u: graph[v]) {
                if ((weights[u] >> bit) & 1) {
                    cnt1++;
                } else {
                    cnt0++;
                }
            }
            int bit_v = (weights[v] >> bit) & 1;
            ll paths = 0;

            if (bit_v == 0) {
                paths = (1LL * cnt0 * cnt1) % MOD;
            } else {
                paths = (1LL * cnt0 * (cnt0 - 1) / 2) % MOD;
                paths = (paths + 1LL * cnt1 * (cnt1 - 1) / 2) % MOD;
            }

            ans = (ans + paths * ((1LL << bit) % MOD)) % MOD;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
