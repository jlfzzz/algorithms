#include <bits/stdc++.h>
using namespace std;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
using ll = long long;

class LcaBinaryLifting {
public:
    vector<int> depth;
    vector<ll> dis;
    vector<vector<int>> pa;
    vector<vector<pair<int, int>>> g;
    int N, LOG;

    LcaBinaryLifting(int n, vector<vector<int>> &edges) {
        N = n;
        LOG = bit_width((unsigned) (N + 1));
        g.assign(N + 1, {});
        for (auto &e: edges) {
            int x = e[0], y = e[1], w = e[2];
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }
        depth.assign(N + 1, 0);
        dis.assign(N + 1, 0);
        pa.assign(N + 1, vector<int>(LOG, -1));

        dfs(1, -1);

        for (int j = 0; j + 1 < LOG; ++j) {
            for (int v = 1; v <= N; ++v) {
                if (pa[v][j] != -1)
                    pa[v][j + 1] = pa[pa[v][j]][j];
            }
        }
    }

    void dfs(int x, int fa) {
        pa[x][0] = fa;
        for (auto &ew: g[x]) {
            int y = ew.first, w = ew.second;
            if (y == fa)
                continue;
            depth[y] = depth[x] + 1;
            dis[y] = dis[x] + w;
            dfs(y, x);
        }
    }

    int get_kth_ancestor(int node, int k) {
        for (int i = 0; i < LOG && node != -1; ++i) {
            if (k >> i & 1) {
                node = pa[node][i];
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] > depth[y])
            swap(x, y);
        y = get_kth_ancestor(y, depth[y] - depth[x]);
        if (x == y)
            return x;
        for (int i = LOG - 1; i >= 0; --i) {
            if (pa[x][i] != pa[y][i]) {
                x = pa[x][i];
                y = pa[y][i];
            }
        }
        return pa[x][0];
    }

    ll get_dis(int x, int y) {
        int l = get_lca(x, y);
        return dis[x] + dis[y] - 2 * dis[l];
    }
};

class Solution {
public:
    vector<int> minimumWeight(vector<vector<int>> &edges, vector<vector<int>> &queries) {
        int n = edges.size() + 1;

        vector<vector<int>> e;
        for (auto &edge: edges) {
            e.push_back({edge[0] + 1, edge[1] + 1, edge[2]});
        }

        LcaBinaryLifting lca(n, e);
        vector<int> tin(n + 1);
        int ts = 0;

        auto dfs = [&](auto &&self, int u, int fa) -> void {
            tin[u] = ++ts;
            for (auto &pair: lca.g[u]) {
                int v = pair.first;
                if (v != fa) {
                    self(self, v, u);
                }
            }
        };
        dfs(dfs, 1, 0);

        vector<int> ans;

        for (auto &q: queries) {
            vector<int> p = {q[0] + 1, q[1] + 1, q[2] + 1};

            sort(p.begin(), p.end(), [&](int a, int b) { return tin[a] < tin[b]; });

            ll sum = lca.get_dis(p[0], p[1]) + lca.get_dis(p[1], p[2]) + lca.get_dis(p[2], p[0]);

            ans.push_back(sum / 2);
        }

        return ans;
    }
};
