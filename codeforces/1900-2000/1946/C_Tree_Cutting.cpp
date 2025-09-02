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
    int n, k;
    cin >> n >> k;
    vector g(n + 1, vector<int>());
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    struct Info {
        int l, r, sz;
    };

    auto check = [&](int target) -> bool {
        int cnt = 0;
        auto dfs = [&](this auto &&dfs, int u, int fa) -> Info {
            Info res = {u, u, 1};

            for (int v: g[u]) {
                if (v == fa) {
                    continue;
                }

                auto [l, r, sz] = dfs(v, u);
                if (sz != 0) {
                    res.l = min(l, res.l);
                    res.r = max(r, res.r);
                    res.sz += sz;
                }
            }

            if (res.sz >= target) {
                cnt++;
                return {0, 0, 0};
            }

            return res;
        };

        dfs(1, -1);

        return cnt >= k + 1;
    };

    int lo = 1;
    int hi = n + 1;
    int ans = 1;

    while (lo < hi) {
        int m = (lo + hi) / 2;
        if (check(m)) {
            ans = m;
            lo = m + 1;
        } else {
            hi = m;
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
