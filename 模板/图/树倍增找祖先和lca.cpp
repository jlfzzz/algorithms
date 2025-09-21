//
// Created by 123 on 25-6-15.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

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
