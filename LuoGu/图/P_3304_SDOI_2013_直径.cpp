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
    int n;
    cin >> n;
    vector<vector<pii>> g(n + 1);
    For(i, n - 1) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    vector<int> dis(n + 1), pa(n + 1);
    vector<bool> vis(n + 1);
    int mx = 1;

    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        pa[u] = fa;
        if (dis[u] > dis[mx]) {
            mx = u;
        }
        for (auto &[next, w]: g[u]) {
            if (next == fa)
                continue;
            dis[next] = dis[u] + w;
            dfs(next, u);
        }
    };

    dis[1] = 0;
    dfs(1, -1);

    ranges::fill(dis, 0);
    dfs(mx, -1);

    cout << dis[mx] << "\n";
    int R = mx;

    for (int i = R; i != -1; i = pa[i]) {
        vis[i] = true;
    }

    int ansR = -1, ansL = -1;
    for (int i = R; i != -1; i = pa[i]) {
        int maxDist = 0;
        auto dfs3 = [&](this auto &&dfs3, int u, int fa, int dist) -> void {
            maxDist = max(maxDist, dist);
            for (auto &[v, w]: g[u]) {
                if (v == fa || vis[v])
                    continue;
                dfs3(v, u, dist + w);
            }
        };
        dfs3(i, -1, 0);

        if (maxDist == dis[R] - dis[i]) {
            ansR = i;
        }
        if (maxDist == dis[i]) {
            ansL = i;
            break;
        }
    }

    int cnt = 0;
    while (ansR != ansL) {
        cnt++;
        ansR = pa[ansR];
    }
    cout << cnt << "\n";
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
