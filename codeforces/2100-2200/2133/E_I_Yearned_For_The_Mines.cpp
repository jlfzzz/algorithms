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
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<std::pair<int, int>> ans;
    std::vector<bool> del(n);

    [&](this auto &&self, int x, int p) -> int {
        int s = 1;
        for (auto y: adj[x]) {
            if (y == p) {
                continue;
            }
            s += self(y, x);
        }
        if (s >= 4) {
            del[x] = true;
            ans.emplace_back(2, x + 1);
            s = 0;
        }
        return s;
    }(0, -1);

    std::vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        for (auto j: adj[i]) {
            if (!del[i] && !del[j]) {
                deg[i]++;
            }
        }
    }

    std::vector<bool> vis(n);
    for (int x = 0; x < n; x++) {
        if (vis[x] || deg[x] > 1) {
            continue;
        }

        [&](this auto &&self, int x) -> void {
            vis[x] = true;
            ans.emplace_back(1, x + 1);
            for (auto y: adj[x]) {
                if (del[x] || del[y] || vis[y]) {
                    continue;
                }
                self(y);
            }
        }(x);
    }

    std::cout << ans.size() << "\n";
    for (auto [x, y]: ans) {
        std::cout << x << " " << y << "\n";
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
