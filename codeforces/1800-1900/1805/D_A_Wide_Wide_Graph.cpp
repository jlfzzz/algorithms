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
    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    auto dfs = [&](auto &&dfs, int u, int fa, vector<int> &dis) -> void {
        dis[u] = dis[fa] + 1;
        for (int v: g[u]) {
            if (v == fa)
                continue;
            dfs(dfs, v, u, dis);
        }
    };

    vector<int> dis(n + 1);
    dis.assign(n + 1, 0);
    dis[0] = -1;
    dfs(dfs, 1, 0, dis);

    int mx = 1;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[mx])
            mx = i;
    }

    int p1 = mx;
    fill(dis.begin(), dis.end(), 0);
    dis[0] = -1;
    dfs(dfs, p1, 0, dis);

    int p2 = 1;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[p2])
            p2 = i;
    }

    vector<int> dis2(n + 1);
    dis2.assign(n + 1, 0);
    dis2[0] = -1;
    dfs(dfs, p2, 0, dis2);

    vector<vector<int>> v1(n + 1), v2(n + 1);
    for (int i = 1; i <= n; i++) {
        if (dis[i] >= 0 && dis[i] <= n)
            v1[dis[i]].push_back(i);
        if (dis2[i] >= 0 && dis2[i] <= n)
            v2[dis2[i]].push_back(i);
    }

    set<int> st1, st2;

    vector<int> ans;
    int comp = 1;
    vector<int> vis(n + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int x: v1[i]) {
            if (st2.count(x)) {
                st2.erase(x);
                if (!vis[x]) {
                    comp++;
                }
                vis[x] = 1;
            } else {
                st1.insert(x);
            }
        }

        for (int x: v2[i]) {
            if (st1.count(x)) {
                st1.erase(x);
                if (!vis[x]) {
                    comp++;
                }
                vis[x] = 1;
            } else {
                st2.insert(x);
            }
        }

        ans.push_back(min<int>(comp, n));
    }

    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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
