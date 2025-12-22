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

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

bool has_edge(const vvi &adj, int u, int v) {
    // 总是由于度数小的去找度数大的，或者二分查找
    // 这里统一在 adj[u] 里找 v
    auto it = lower_bound(all(adj[u]), v);
    return it != adj[u].end() && *it == v;
}

void solve() {
    int n, m;
    rd(n, m);

    vvi adj(n + 1);
    vi deg(n + 1, 0);

    F(i, 1, m) {
        int u, v;
        rd(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u]++;
        deg[v]++;
    }

    // 关键优化：排序邻接表，以便使用二分查找快速判断边是否存在
    F(i, 1, n) { sort(all(adj[i])); }

    int win_count = 0;

    F(u, 1, n) {
        if (deg[u] >= 4) {
            win_count++;
        } else if (deg[u] == 2) {
            // 孩子 a, b
            int a = adj[u][0];
            int b = adj[u][1];

            // 检查 a 和 b 是否直接相连
            // 使用二分查找，复杂度 O(log N)
            bool connected = has_edge(adj, a, b);

            // 计算有效孙子数量 (Valid Grandchildren)
            // 原始度数 - 1(父节点u) - (如果兄弟节点也是邻居则减1)
            int gc_a = deg[a] - 1 - (connected ? 1 : 0);
            int gc_b = deg[b] - 1 - (connected ? 1 : 0);

            // 条件：每个孩子都必须有至少 2 个孙子
            if (gc_a >= 2 && gc_b >= 2) {
                win_count++;
            }
        } else if (deg[u] == 3) {
            // 孩子 a, b, c
            int a = adj[u][0];
            int b = adj[u][1];
            int c = adj[u][2];

            // 检查孩子之间的连接情况
            bool ab = has_edge(adj, a, b);
            bool ac = has_edge(adj, a, c);
            bool bc = has_edge(adj, b, c);

            // 计算每个孩子的有效孙子数
            // 减去父节点u，再减去连接的兄弟节点
            int gc_a = deg[a] - 1 - (ab ? 1 : 0) - (ac ? 1 : 0);
            int gc_b = deg[b] - 1 - (ab ? 1 : 0) - (bc ? 1 : 0);
            int gc_c = deg[c] - 1 - (ac ? 1 : 0) - (bc ? 1 : 0);

            // 条件：至少有 2 个孩子拥有至少 1 个孙子
            int valid_children = 0;
            if (gc_a >= 1)
                valid_children++;
            if (gc_b >= 1)
                valid_children++;
            if (gc_c >= 1)
                valid_children++;

            if (valid_children >= 2) {
                win_count++;
            }
        }
    }

    prt(win_count);
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
