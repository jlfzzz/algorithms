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

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    int count;

    explicit UnionFind(const int n) : count(n) {
        parent.resize(n);
        rank.resize(n);
        ranges::fill(rank, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return false;
        }

        if (rank[root_x] == rank[root_y]) {
            parent[root_x] = root_y;
            rank[root_y] += 1;
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        } else {
            parent[root_x] = root_y;
        }
        count--;
        return true;
    }
};

constexpr int N = 2e5 + 5;
int n, m;

struct E {
    ll u, v, w;
    bool operator<(const E &other) const { return this->w < other.w; }
};

vector<E> e, e2;
constexpr int LOG = 21;
ll depth[N], dis[N];
vp g[N];
int parent[N][LOG];

int Multitest = 0;

void init() {}

void dfs(int u, int fa, ll d) {
    parent[u][0] = fa;
    dis[u] = d;
    for (auto [v, w]: g[u]) {
        if (v != fa) {
            depth[v] = depth[u] + 1;
            dfs(v, u, d + w);
        }
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    D(i, LOG - 1, 0) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v)
        return u;
    D(i, LOG - 1, 0) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

ll get_dist(int u, int v) {
    int lca = get_lca(u, v);
    return dis[u] + dis[v] - 2 * dis[lca];
}

void solve() {
    rd(n, m);

    F(i, 1, m) {
        int u, v, w;
        rd(u, v, w);
        u--, v--;
        e.pb(u, v, w);
    }

    sort(all(e));
    UnionFind uf(n);
    F(i, 0, n) F(j, 0, LOG - 1) parent[i][j] = -1;

    for (auto [u, v, w]: e) {
        if (uf.unite(u, v)) {
            g[u].pb(v, w);
            g[v].pb(u, w);
        } else {
            e2.pb(u, v, w);
        }
    }

    depth[0] = 0;
    dfs(0, -1, 0);

    F(i, 1, LOG - 1) {
        F(x, 0, n - 1) {
            int px = parent[x][i - 1];
            if (px != -1) {
                parent[x][i] = parent[px][i - 1];
            }
        }
    }

    for (auto [u, v, w]: e2) {
        if (get_dist(u, v) > w) {
            prt("NO");
            return;
        }
    }

    prt("YES");
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
