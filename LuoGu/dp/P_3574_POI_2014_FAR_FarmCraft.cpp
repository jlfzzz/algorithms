#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
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

    template<typename... Args>
    void prt(const Args &...args) {
        ((cout << args << " "), ...);
        cout << "\n";
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

    vector<int> costs(n + 1);
    rd_vec(costs, 1);

    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        rd(u, v);

        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dp(n + 1);
    vector<int> subtree_size(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> int {
        int sz = 1;

        vector<int> children;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }
            int child_sz = dfs(v, u);
            sz += child_sz;
            children.push_back(v);
        }

        ranges::sort(children,
                     [&](int a, int b) { return (dp[a] - 2 * subtree_size[a]) > (dp[b] - 2 * subtree_size[b]); });

        int cost = 0;
        int total = 0;
        for (int v: children) {
            total = max(total, 1 + cost + dp[v]);
            cost += subtree_size[v] * 2;
        }

        dp[u] = max(total, costs[u]);
        subtree_size[u] = sz;
        return sz;
    };

    dfs(1, -1);
    int answer = max(dp[1], 2 * (n - 1) + costs[1]);
    prt(answer);
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
