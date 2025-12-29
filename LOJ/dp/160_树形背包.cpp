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

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, w;
    rd(n, w);

    // 原始数据
    vi raw_d(n + 1);
    vl raw_weights(n + 1), raw_vals(n + 1);
    rv(raw_d, 1);
    rv(raw_weights, 1);
    rv(raw_vals, 1);

    // 建图 (0 为虚拟根)
    vvi g(n + 1);
    F(i, 1, n) { g[raw_d[i]].pb(i); }

    // --- DFS 序预处理 ---
    // new_w, new_v: 按照 DFS 序重排后的重量和价值
    // sub_sz: 记录该节点(包含子树)的节点数量，用于跳跃
    vl new_w(n + 2), new_v(n + 2);
    vi sub_sz(n + 2);
    int timer = 0;

    timer = 0;
    auto dfs_build = [&](auto &&self, int u) -> int {
        int my_id = ++timer; // 分配 DFS 序 ID
        new_w[my_id] = (u == 0 ? 0 : raw_weights[u]);
        new_v[my_id] = (u == 0 ? 0 : raw_vals[u]);
        int sz = 1;
        for (int v: g[u]) {
            sz += self(self, v);
        }
        sub_sz[my_id] = sz;
        return sz;
    };

    dfs_build(dfs_build, 0);

    // --- 线性 DP ---
    // dp[i][j]: 从 DFS 序第 i 个物品开始考虑，容量为 j 的最大值
    // 空间可以优化成 1D，也可以直接用 vector<long long> 滚动
    // 为了稳妥，用 n+2 行 (0..n+1)
    // 注意：timer 最终是 n+1 (包含0号节点)

    // 我们使用滚动数组或者两行，或者直接 N 行 (如果 N*W 不大)
    // 假设 N,W <= 2000，二维数组完全没问题且最快
    // 这里使用 vector<vector> 但是一次性分配，比递归中反复用好得多
    // 甚至可以直接用一维数组倒着推（类似01背包），但 DFS 序通常是从后往前推 i

    vvl dp(timer + 2, vl(w + 1, 0));

    // 从后往前枚举 DFS 序
    D(i, timer, 1) {
        F(j, 0, w) {
            // 选项1: 不选物品 i，必须跳过整棵子树
            // 下一个状态是 i + sub_sz[i]
            // 如果越界了(后面没了)，就是 0
            ll val_skip = (i + sub_sz[i] > timer) ? 0 : dp[i + sub_sz[i]][j];

            // 选项2: 选物品 i，处理下一个物品 i + 1
            // 前提：容量够，且不是强制不选的情况(比如依赖没满足? 不，DFS序天然满足依赖)
            ll val_pick = 0;
            if (j >= new_w[i]) {
                val_pick = dp[i + 1][j - new_w[i]] + new_v[i];
            } else {
                val_pick = -INF; // 容量不够不能选
            }

            dp[i][j] = max(val_skip, val_pick);
        }
    }

    // 答案是 dp[1][w] (因为 1 号是虚拟根 0，它的重量是 0)
    // 如果题目要求不能算虚拟根的 value (本身是0)，那正好
    // 但是虚拟根必须选（作为入口），它的 w=0，所以一定能选上
    prt(dp[1][w]);
}

// void solve() {
//     int n, w;
//     rd(n, w);

//     vl d(n + 1), weights(n + 1), vals(n + 1);
//     rv(d, 1);
//     rv(weights, 1);
//     rv(vals, 1);

//     vvi g(n + 1);
//     F(i, 1, n) { g[d[i]].pb(i); }

//     vvl dp(n + 1, vl(w + 1));
//     vi sz(n + 1);

//     auto dfs = [&](auto &&dfs, int u, int fa) -> void {
//         int we = weights[u];
//         ll val = vals[u];

//         sz[u] = we;
//         F(j, we, w) dp[u][j] = val;

//         for (int v: g[u]) {
//             if (v == fa)
//                 continue;

//             dfs(dfs, v, u);

//             int mx = min(w, sz[u] + sz[v]);

//             for (int j = mx; j >= we; j--) {
//                 int KK = min(sz[v], j - we);

//                 for (int k = 0; k <= KK; k++) {
//                     dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[v][k]);
//                 }
//             }
//             sz[u] += sz[v];
//         }
//     };

//     dfs(dfs, 0, -1);
//     prt(dp[0][w]);
// }


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
