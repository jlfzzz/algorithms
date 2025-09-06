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

    vector<int> par(n + 1);
    For(i, m) {
        int u, v;
        cin >> u >> v;
        par[u] ^= 1;
        par[v] ^= 1;
    }

    int odd = 0;
    for (int i = 1; i <= n; i++)
        odd += (par[i] & 1);

    int total = n * (n - 1) / 2;
    int t = (n & 1) ? (odd / 2) : ((n - odd) / 2);
    int ans = total - t;
    cout << ans << '\n';
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
