#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace io {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
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
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);

    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    int ans = 0;

    // dpSingles[k] = 已处理分支在深度 k 上“选 1 个点”的方案数（跨分支）
    // dpPairs[k]   = 已处理分支在深度 k 上“选 2 个点”的方案数（跨分支）
    vector<int> dpSingles(n + 2, 0), dpPairs(n + 2, 0);
    // d[k] = 当前分支在深度 k 上的点数
    vector<int> d(n + 2, 0);

    // 分支内 DFS：统计从 r 的某个相邻点 v 出发的各深度点数
    auto dfs = [&](auto &&self, int u, int parent, int depth) -> void {
        d[depth]++;
        for (int w: g[u]) {
            if (w == parent)
                continue;
            self(self, w, u, depth + 1);
        }
    };

    for (int r = 1; r <= n; r++) {
        int deg = (int) g[r].size();
        if (deg < 3)
            continue;

        fill(all(dpSingles), 0);
        fill(all(dpPairs), 0);

        for (int v: g[r]) {
            fill(all(d), 0);
            int maxDepth = 0;
            // 统计该分支各深度点数
            dfs(dfs, v, r, 1);
            // 找到该分支最大深度（避免整段 n 的遍历浪费）
            for (int k = (int) d.size() - 1; k >= 1; k--) {
                if (d[k]) {
                    maxDepth = k;
                    break;
                }
            }
            // 跨分支 DP 合并
            for (int k = 1; k <= maxDepth; k++) {
                ans += dpPairs[k] * d[k]; // 选 3 个点：已有“选 2 个”× 当前分支“选 1 个”
                dpPairs[k] += dpSingles[k] * d[k]; // 选 2 个点：已有“选 1 个”× 当前分支“选 1 个”
                dpSingles[k] += d[k]; // 选 1 个点：累加当前分支
            }
        }
    }

    prt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
