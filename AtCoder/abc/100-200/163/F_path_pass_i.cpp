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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    ll n;
    rd(n);
    vi col(n + 1);
    rv(col, 1);

    vvi g(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    auto sum = [&](ll x) -> ll { return x * (x + 1) / 2; };

    vl sz(n + 1), ans(n + 1), cnt(n + 1);
    F(i, 1, n) { ans[i] = sum(n); }

    auto dfs = [&](auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;
        int c = col[u];
        ll tmp = cnt[c];
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }
            ll t = cnt[c];
            dfs(dfs, v, u);
            ll ad = cnt[c] - t;
            sz[u] += sz[v];
            ans[c] -= sum(sz[v] - ad);
        }
        cnt[c] = tmp + sz[u];
    };
    dfs(dfs, 1, 0);

    F(i, 1, n) { prt(ans[i] - sum(n - cnt[i])); }
}

// 启发式合并
/*
#pragma comment(linker, "/STACK:102400000,102400000")

constexpr int N = 200005;

int n;
int col[N];
vector<int> g[N];
ll sz[N];
ll ans[N];
int son[N]; // 重儿子

// 计算 n*(n+1)/2
ll calc(ll x) {
    return x * (x + 1) / 2;
}

// 第一次DFS：计算子树大小和重儿子
void dfs_sz(int u, int fa) {
    sz[u] = 1;
    son[u] = 0;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
}

// DSU on Tree 主要逻辑
// 返回一个 map 指针，存储当前子树每种颜色的“阻断大小之和”
map<int, ll>* dfs_dsu(int u, int fa) {
    map<int, ll>* cur_mp;

    // 1. 优先处理重儿子
    if (son[u]) {
        cur_mp = dfs_dsu(son[u], u);

        // 处理重儿子这边的连通块对 color[u] 的贡献
        // 重儿子子树中，能延伸到 u 的不含 color[u] 的连通块大小 = sz[son[u]] - blocked_size
        int c = col[u];
        ll blocked = 0;
        if (cur_mp->count(c)) blocked = (*cur_mp)[c];

        ll rem = sz[son[u]] - blocked;
        ans[c] -= calc(rem);
    } else {
        cur_mp = new map<int, ll>();
    }

    // 2. 处理轻儿子并合并
    for (int v : g[u]) {
        if (v == fa || v == son[u]) continue;

        map<int, ll>* child_mp = dfs_dsu(v, u);

        // 处理轻儿子这边的连通块对 color[u] 的贡献
        int c = col[u];
        ll blocked = 0;
        if (child_mp->count(c)) blocked = (*child_mp)[c];

        ll rem = sz[v] - blocked;
        ans[c] -= calc(rem);

        // 启发式合并：将小的 map 合并到大的 map (这里实际上是将轻儿子合并到重儿子)
        // 虽然我们已经让 cur_mp 指向重儿子，但为了通用性，这里直接遍历轻儿子 map
        for (auto& [color, val] : *child_mp) {
            (*cur_mp)[color] += val;
        }
        delete child_mp; // 释放轻儿子 map 内存
    }

    // 3. 更新 u 节点自身对 color[u] 的阻断信息
    // u 变成了 color[u] 的最高阻断点，它覆盖了下面所有同色的阻断
    (*cur_mp)[col[u]] = sz[u];

    return cur_mp;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> col[i];
        ans[i] = calc(n); // 初始化为总路径数
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_sz(1, 0);

    // 执行 DSU on Tree
    map<int, ll>* root_mp = dfs_dsu(1, 0);

    // 4. 处理整棵树剩余的部分（包含根节点的连通块）
    // 对于每种颜色，root_mp[c] 记录了所有被该颜色切断的子树大小之和
    // 剩下的 N - root_mp[c] 就是包含根节点的那个不含颜色 c 的连通块大小
    for (int c = 1; c <= n; c++) {
        ll blocked = 0;
        if (root_mp->count(c)) blocked = (*root_mp)[c];
        ll rem = n - blocked;
        ans[c] -= calc(rem);
    }

    delete root_mp;

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
}
*/

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
