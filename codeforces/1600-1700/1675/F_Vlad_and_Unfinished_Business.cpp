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

int Multitest = 1;

void init() {}

void solve() {
    int n, k;
    rd(n, k);

    int x, y;
    rd(x, y);

    vector<int> a(k);
    rd_vec(a);



    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        rd(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> path;
    auto dfs = [&](this auto &&dfs, int u, int fa) -> bool {
        path.push_back(u);
        if (u == y) {
            return true;
        }

        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            if (dfs(v, u)) {
                return true;
            }
        }

        path.pop_back();
        return false;
    };

    dfs(x, -1);

    int m = (int) path.size();
    vector<int> need(n + 1, 0);
    for (int v: path)
        need[v] = 1;
    for (int v: a)
        need[v] = 1;

    int tot = 0;
    for (int i = 1; i <= n; i++)
        tot += need[i];

    int edges = 0;
    auto dfs_cnt = [&](this auto &&dfs_cnt, int u, int fa) -> int {
        int s = need[u];
        for (int v: g[u])
            if (v != fa) {
                int t = dfs_cnt(v, u);
                if (t > 0 && t < tot)
                    edges++;
                s += t;
            }
        return s;
    };

    dfs_cnt(x, 0);
    int dis = m ? (m - 1) : 0;
    int ans = edges * 2 - dis;
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
