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

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400005; // 重构树有 2N-1 个点
const int LOGN = 20;

struct Edge {
    int u, v, w;

    // 升序
    bool operator<(const Edge &other) const { return w < other.w; }
} edges[MAXN];

vector<int> adj[MAXN * 2];
int val[MAXN * 2]; // 点权：1~n为0(或原点权)，n+1~cnt为边权
int fa[MAXN * 2][LOGN]; // 倍增数组
int dep[MAXN * 2]; // 深度
int p[MAXN * 2]; // 并查集数组
int cnt;

ll ans[MAXN * 2];
int sz[MAXN * 2];

int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }

void build_kruskal_tree(int n, int m) {
    // 1. 初始化
    for (int i = 1; i <= n * 2; i++) {
        p[i] = i;
        adj[i].clear();
        sz[i] = 1;
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

void dfs(int u, ll sum) {
    if (adj[u].empty()) {
        ans[u] = sum + val[u];
        return;
    }

    int l = adj[u][0];
    int r = adj[u][1];

    dfs(l, sum + 1ll * val[u] * sz[r]);

    dfs(r, sum + 1ll * val[u] * sz[l]);
}

// void dfs(int u, int d) {
//     dep[u] = d;
//     for (int i = 1; i < LOGN; i++) {
//         fa[u][i] = fa[fa[u][i - 1]][i - 1];
//     }
//     for (int v: adj[u]) {
//         fa[v][0] = u;
//         dfs(v, d + 1);
//     }
// }

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


constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vi a(n + 1);
    rv(a, 1);

    F(i, 1, n) {
        val[i] = a[i];
        sz[i] = 1;
        adj[i].clear();
        ans[i] = 0;
    }

    F(i, 1, m) {
        int u, v;
        rd(u, v);
        edges[i] = {u, v, max(a[u], a[v])};
    }

    build_kruskal_tree(n, m);

    dfs(cnt, 0);

    F(i, 1, n) { cout << ans[i] << (i == n ? "" : " "); }
    cout << "\n";
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
