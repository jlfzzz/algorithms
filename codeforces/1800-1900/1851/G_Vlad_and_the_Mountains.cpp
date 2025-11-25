#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
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
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
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

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            return true;
        }
        return false;
    }
};

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const { return w < other.w; }
};

int n, m;
vector<int> h;
vector<vector<pair<int, int>>> adj;
vector<vector<int>> up;
vector<vector<int>> max_w;
vector<int> depth;
vector<int> visited;
int LOG;

void dfs(int u, int p, int w, int d) {
    depth[u] = d;
    up[u][0] = p;
    max_w[u][0] = w;
    visited[u] = 1;

    for (int i = 1; i <= LOG; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        max_w[u][i] = max(max_w[u][i - 1], max_w[up[u][i - 1]][i - 1]);
    }

    for (auto &edge: adj[u]) {
        int v = edge.first;
        int weight = edge.second;
        if (v != p) {
            dfs(v, u, weight, d + 1);
        }
    }
}

int queryMax(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int res = 0;

    for (int i = LOG; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            res = max(res, max_w[u][i]);
            u = up[u][i];
        }
    }

    if (u == v)
        return res;

    for (int i = LOG; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            res = max(res, max_w[u][i]);
            res = max(res, max_w[v][i]);
            u = up[u][i];
            v = up[v][i];
        }
    }

    res = max(res, max_w[u][0]);
    res = max(res, max_w[v][0]);

    return res;
}

void solve() {
    rd(n, m);
    h.resize(n + 1);
    rv(h, 1);

    vector<Edge> edges;
    F(i, 1, m) {
        int u, v;
        rd(u, v);
        edges.pb(u, v, max(h[u], h[v]));
    }

    sort(all(edges));
    DSU dsu(n);
    adj.assign(n + 1, vector<pair<int, int>>());

    for (auto [u, v, w]: edges) {
        if (dsu.unite(u, v)) {
            adj[u].pb(v, w);
            adj[v].pb(u, w);
        }
    }

    LOG = 0;
    while ((1 << (LOG + 1)) <= n)
        LOG++;

    up.assign(n + 1, vector<int>(LOG + 1));
    max_w.assign(n + 1, vector<int>(LOG + 1));
    depth.assign(n + 1, 0);
    visited.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, i, 0, 0);
        }
    }

    int q;
    rd(q);
    while (q--) {
        int a, b;
        ll e;
        rd(a, b, e);

        if (dsu.find(a) != dsu.find(b)) {
            prt("NO");
            continue;
        }

        int mx = queryMax(a, b);

        if (h[a] + e >= mx) {
            prt("YES");
        } else {
            prt("NO");
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--) {
        solve();
    }
}
