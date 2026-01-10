#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005; // 重构树有 2N-1 个点
const int LOGN = 20;
using ll = long long;

struct Edge {
    ll u, v, w;

    // 升序
    bool operator<(const Edge &other) const { return w < other.w; }
} edges[MAXN];

vector<int> adj[MAXN * 2];
int val[MAXN * 2]; // 点权：1~n为0(或原点权)，n+1~cnt为边权
int fa[MAXN * 2][LOGN]; // 倍增数组
int dep[MAXN * 2]; // 深度
int p[MAXN * 2]; // 并查集数组
int sz[MAXN * 2];
int cnt;

int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

void build_kruskal_tree(int n, int m) {
    for (int i = 1; i <= n * 2; i++) {
        p[i] = i;
        adj[i].clear();
    }
    cnt = n;

    sort(edges + 1, edges + 1 + m);

    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            cnt++;
            val[cnt] = w;
            sz[cnt] = sz[root_u] + sz[root_v];

            p[root_u] = p[root_v] = cnt;

            adj[cnt].push_back(root_u);
            adj[cnt].push_back(root_v);
        }
    }
}

void dfs(int u, int d) {
    dep[u] = d;
    for (int i = 1; i < LOGN; i++) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    }
    for (int v: adj[u]) {
        fa[v][0] = u;
        dfs(v, d + 1);
    }
}

void init_lca() {
    for (int i = cnt; i >= 1; --i) {
        if (!dep[i])
            dfs(i, 1);
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = LOGN - 1; i >= 0; i--) {
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if (u == v)
        return u;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
