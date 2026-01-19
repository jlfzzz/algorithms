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
#define us unsigned
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

class DSU {
public:
    vector<int> parent;
    vector<int> rank;
    int count;

    explicit DSU(const int n) : count(n) {
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

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    struct Edge {
        int u, v, w, id;
    };
    vector<Edge> edges;
    edges.reserve(m);

    F(i, 1, m) {
        int u, v, w;
        rd(u, v, w);
        u--, v--;
        edges.pb(Edge{u, v, w, i});
    }

    DSU uf1(n), uf2(n);

    // 1. 把所有偶数边加入 uf1
    // uf1 维护的是：如果只选偶数边，哪些点是连通的
    for (auto &e: edges) {
        if (e.w % 2 == 0) {
            uf1.unite(e.u, e.v);
        }
    }

    vector<int> used(m + 1, 0);
    int odd_cnt = 0;

    // 2. 选取“刚需”的奇数边
    // 如果一条奇数边连接了 uf1 中两个原本断开的连通块，说明这条边是沟通两个偶数连通块的桥梁，必须选
    for (auto &e: edges) {
        if (e.w % 2 != 0) {
            // 注意：这里要 update uf1，模拟把这两个块连起来了
            if (uf1.unite(e.u, e.v)) {
                uf2.unite(e.u, e.v);
                used[e.id] = 1;
                odd_cnt++;
            }
        }
    }

    // 3. 如果奇数边数量是奇数，必须再补一条非必须的奇数边
    if (odd_cnt % 2 != 0) {
        for (auto &e: edges) {
            if (e.w % 2 != 0 && !used[e.id]) {
                // 只要在 uf2 (答案树) 中不构成环，就可以加
                if (uf2.unite(e.u, e.v)) {
                    used[e.id] = 1;
                    odd_cnt++;
                    break;
                }
            }
        }
    }

    // 如果补完还是奇数（或者根本没法补），说明无解
    if (odd_cnt % 2 != 0) {
        prt("NO");
        return;
    }

    // 4. 填补偶数边，直到连通
    for (auto &e: edges) {
        if (e.w % 2 == 0) {
            if (uf2.unite(e.u, e.v)) {
                used[e.id] = 1;
            }
        }
    }

    // 收集答案并检查是否连通 (选了 n-1 条边)
    vector<int> ans;
    for (auto &e: edges) {
        if (used[e.id]) {
            ans.pb(e.id);
        }
    }

    if (SZ(ans) != n - 1) {
        prt("NO");
    } else {
        prt("YES");
        prv(ans);
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
