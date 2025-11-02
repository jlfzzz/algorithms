#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
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

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);
    vvi g(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }
    const int half = n / 2;

    vi sz(n + 1), dp1(n + 1), dp2(n + 1), msz(n + 1), msz2(n + 1), Ans(n + 1);

    auto dfs1 = [&](this auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;
        dp1[u] = 0;
        msz[u] = 0;
        msz2[u] = 0;
        for (int v: g[u]) {
            if (v == fa)
                continue;
            dfs(v, u);
            sz[u] += sz[v];
            dp1[u] = max(dp1[u], dp1[v]);
            if (sz[msz[u]] < sz[v]) {
                msz2[u] = msz[u];
                msz[u] = v;
            } else if (sz[msz2[u]] < sz[v]) {
                msz2[u] = v;
            }
        }
        if (sz[u] <= half)
            dp1[u] = sz[u];
    };
    dfs1(1, 0);

    auto dfs2 = [&](this auto &&dfs, int u, int fa) -> void {
        for (int v: g[u]) {
            if (v == fa)
                continue;
            if (n - sz[v] <= half)
                dp2[v] = n - sz[v];
            else if (v != msz[u])
                dp2[v] = max(dp2[u], dp1[msz[u]]);
            else
                dp2[v] = max(dp2[u], dp1[msz2[u]]);
            dfs(v, u);
        }
        int upSize = n - sz[u];
        int maxChildSize = sz[msz[u]];
        if (upSize > maxChildSize) {
            Ans[u] = (upSize - dp2[u] <= half);
        } else {
            Ans[u] = (maxChildSize - dp1[msz[u]] <= half);
        }
    };
    dp2[1] = 0;
    dfs2(1, 0);

    prv(Ans, 1);
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
