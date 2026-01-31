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
    string s;
    rd(s);
    int n = SZ(s);

    // 构建二分图
    // 左侧点: 0 ~ n-1
    // 右侧点: n ~ 2n-1
    // 原始边 i->j 转化为无向边: Left(i) - Right(j)
    vvi adj(2 * n);
    F(i, 0, n - 1) {
        int u, v;
        if (s[i] == '0') {
            // 原图: i -> (i+1)%n
            // 二分图: Left(i) - Right((i+1)%n)
            u = i;
            v = n + (i + 1) % n;
        } else {
            // 原图: (i+1)%n -> i
            // 二分图: Left((i+1)%n) - Right(i)
            u = (i + 1) % n;
            v = n + i;
        }
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int match = 0;
    vi vis(2 * n, 0);

    // 遍历所有连通分量 (只可能是链或环)
    F(i, 0, 2 * n - 1) {
        if (vis[i] || adj[i].empty())
            continue;

        int nd = 0; // 节点数
        int ed = 0; // 边数

        // BFS 统计连通分量大小
        vi q;
        q.pb(i);
        vis[i] = 1;
        int hd = 0;

        while (hd < SZ(q)) {
            int u = q[hd++];
            nd++;
            for (auto &v: adj[u]) {
                ed++;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.pb(v);
                }
            }
        }

        ed /= 2; // 无向边被统计了两次

        // 根据分量类型计算最大匹配贡献
        if (nd == ed) {
            // 环 (Cycle): 匹配数为 edges / 2
            match += ed / 2;
        } else {
            // 链 (Path): 匹配数为 ceil(edges / 2) => (edges + 1) / 2
            match += (ed + 1) / 2;
        }
    }

    // 根据 Dilworth 定理推论: 最大反链 = n - 最大匹配
    prt(n - match);
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
