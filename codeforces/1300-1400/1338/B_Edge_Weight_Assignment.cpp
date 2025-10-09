#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
#define pb push_back
#define pf push_front
#define eb emplace_back
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

    vector<int> depth(n + 1);
    int ans2 = n - 1;
    int cnt2 = 0;

    int root = -1;

    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        int cnt = 0;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            depth[v] = depth[u] + 1;
            dfs(v, u);

            if (g[v].size() == 1) {
                cnt++;
            }
        }

        if (fa == root) {
            if (g[root].size() == 1) {
                cnt++;
            }
        }

        if (cnt > 1) {
            cnt2 += cnt - 1;
        }
    };

    for (int i = 1; i <= n; i++) {
        if (g[i].size() == 1) {
            // debug("root", i);
            root = i;
            dfs(i, 0);
            break;
        }
    }


    int c0 = 1, c1 = 0;
    for (int i = 1; i <= n; i++) {
        if (g[i].size() == 1) {
            if (depth[i] & 1) {
                c1++;
            } else {
                c0++;
            }
        }
    }

    int ans1 = 1;
    if (c0 && c1) {
        ans1 = min(3ll, n - 1);
    }
    ans2 -= cnt2;

    prt(ans1, ans2);
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
