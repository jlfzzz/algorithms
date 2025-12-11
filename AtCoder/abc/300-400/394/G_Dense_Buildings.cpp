#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD2 = int(1e9 + 7);
constexpr int MOD = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

namespace utils {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
    }

    template<typename T>
    void prt(const T &x) {
        cout << x << '\n';
    }

    template<typename T, typename... Args>
    void prt(const T &first, const Args &...rest) {
        cout << first;
        ((cout << ' ' << rest), ...);
        cout << '\n';
    }

    template<typename T>
    void prv(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prv(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void rd(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void rd(T &x, Args &...args) {
        cin >> x;
        rd(args...);
    }

    template<typename A, typename B>
    void rd(pair<A, B> &p) {
        cin >> p.first >> p.second;
    }

    template<typename T>
    void rv(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rv(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace utils

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1000005;

struct DSU {
    vector<int> fa;
    DSU(int n) : fa(n) { iota(all(fa), 0); }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
};

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const { return w > other.w; }
};

int h, w;
int grid[N];
int val[N];
vector<int> adj[N];
int up[N][21], dep[N];
int tot_nodes;

inline int get_id(int r, int c) { return r * w + c; }

void dfs(int u, int p) {
    dep[u] = dep[p] + 1;
    up[u][0] = p;
    F(i, 1, 20) up[u][i] = up[up[u][i - 1]][i - 1];
    for (int v: adj[u]) {
        dfs(v, u);
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    D(i, 20, 0) {
        if (dep[up[u][i]] >= dep[v])
            u = up[u][i];
    }
    if (u == v)
        return u;
    D(i, 20, 0) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void solve() {
    rd(h, w);

    int max_nodes = 2 * h * w + 10;
    F(i, 0, max_nodes) adj[i].clear();

    F(i, 0, h - 1) {
        F(j, 0, w - 1) { rd(grid[get_id(i, j)]); }
    }

    tot_nodes = h * w;
    F(i, 0, tot_nodes - 1) { val[i] = grid[i]; }

    vector<Edge> edges;
    edges.reserve(2 * h * w);

    F(i, 0, h - 1) {
        F(j, 0, w - 1) {
            int u = get_id(i, j);
            if (j + 1 < w) {
                int v = get_id(i, j + 1);
                edges.pb(Edge{u, v, min(grid[u], grid[v])});
            }
            if (i + 1 < h) {
                int v = get_id(i + 1, j);
                edges.pb(Edge{u, v, min(grid[u], grid[v])});
            }
        }
    }

    sort(all(edges));

    DSU dsu(max_nodes);

    for (auto &e: edges) {
        int u = dsu.find(e.u);
        int v = dsu.find(e.v);
        if (u != v) {
            int new_node = tot_nodes++;
            val[new_node] = e.w;

            adj[new_node].pb(u);
            adj[new_node].pb(v);

            dsu.fa[u] = dsu.fa[v] = new_node;
        }
    }

    if (tot_nodes > 0) {
        dfs(tot_nodes - 1, tot_nodes - 1);
    }

    int q;
    rd(q);
    while (q--) {
        int r1, c1, r2, c2, y, z;
        rd(r1, c1, y, r2, c2, z);
        --r1;
        --c1;
        --r2;
        --c2;

        int u = get_id(r1, c1);
        int v = get_id(r2, c2);

        if (u == v) {
            prt(abs(y - z));
            continue;
        }

        int lca = get_lca(u, v);
        int bottleneck = val[lca];

        if (bottleneck >= min(y, z)) {
            prt(abs(y - z));
        } else {
            prt(y + z - 2 * bottleneck);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve();
    }
}
