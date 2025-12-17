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

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);

    vvi edges;
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        //u--, v--;
        edges.pb(vi{u, v, 1});
    }

    LcaBinaryLifting lca(n, edges);

    int q;
    rd(q);

    F(i, 1, q) {
        int x, y, a, b, k;
        rd(x, y, a, b, k);
        //x--, y--, a--, b--;

        int d1 = lca.get_dis(a, b);
        if (d1 <= k && ((d1 % 2) == (k % 2))) {
            prt("YES");
            continue;
        }

        int d2 = lca.get_dis(a, x) + 1 + lca.get_dis(y, b);
        d1 = d2;
        if (d1 <= k && ((d1 % 2) == (k % 2))) {
            prt("YES");
            continue;
        }

        d2 = lca.get_dis(a, y) + 1 + lca.get_dis(x, b);
        d1 = d2;
        if (d1 <= k && ((d1 % 2) == (k % 2))) {
            prt("YES");
            continue;
        }

        prt("NO");
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
