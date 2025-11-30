#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int MAXN = 400005;
constexpr int MAX_SEQ = 800005;
constexpr int LOGN = 21;

struct Edge {
    int to, next;
} tree_edges[MAXN * 2];
int head[MAXN], tot_edge;

int val[MAXN];
int depth[MAXN];
int dfn[MAXN];
int seq[MAX_SEQ];
int st[LOGN][MAX_SEQ];
int Log[MAX_SEQ];
int clk;

struct InputEdge {
    int u, v, w;
} edges[200005];

struct UnionFind {
    int parent[MAXN];
    void init(int n) {
        for (int i = 0; i <= 2 * n; ++i)
            parent[i] = i;
    }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
} uf;

inline void add_edge(int u, int v) {
    tree_edges[++tot_edge] = {v, head[u]};
    head[u] = tot_edge;
}

void dfs(int u, int d) {
    depth[u] = d;
    seq[++clk] = u;
    dfn[u] = clk;
    for (int i = head[u]; i; i = tree_edges[i].next) {
        int v = tree_edges[i].to;
        dfs(v, d + 1);
        seq[++clk] = u;
    }
}

void build_st(int len) {
    Log[1] = 0;
    for (int i = 2; i <= len; i++)
        Log[i] = Log[i >> 1] + 1;

    for (int i = 1; i <= len; i++)
        st[0][i] = seq[i];

    for (int j = 1; j < LOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= len; i++) {
            int u = st[j - 1][i];
            int v = st[j - 1][i + (1 << (j - 1))];
            st[j][i] = (depth[u] < depth[v]) ? u : v;
        }
    }
}

inline int getLCA(int u, int v) {
    int l = dfn[u], r = dfn[v];
    if (l > r)
        swap(l, r);
    int k = Log[r - l + 1];
    int x = st[k][l];
    int y = st[k][r - (1 << k) + 1];
    return depth[x] < depth[y] ? x : y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m))
        return 0;

    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges + 1, edges + m + 1, [](const InputEdge &a, const InputEdge &b) { return a.w < b.w; });

    uf.init(n);
    int cnt = n;

    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        int root_u = uf.find(u);
        int root_v = uf.find(v);

        if (root_u != root_v) {
            cnt++;
            val[cnt] = w;
            add_edge(cnt, root_u);
            add_edge(cnt, root_v);
            uf.parent[root_u] = cnt;
            uf.parent[root_v] = cnt;
            uf.parent[cnt] = cnt;
        }
    }

    if (cnt > 0)
        dfs(cnt, 1);
    build_st(clk);

    int q;
    cin >> q;
    ll A, B, C, P;
    cin >> A >> B >> C >> P;

    auto rnd = [&]() -> int { return A = (A * B + C) % P; };

    ll ans = 0;
    while (q--) {
        int u = rnd() % n + 1;
        int v = rnd() % n + 1;
        if (u != v) {
            ans = (ans + val[getLCA(u, v)]) % 1000000007;
        }
    }

    cout << ans << "\n";
    return 0;
}
