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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);

    vvi g(n + 1);
    F(i, 1, n - 1) {
        int a, b;
        rd(a, b);
        g[a].pb(b);
        g[b].pb(a);
    }

    vvi dp0(n + 1), dp1(n + 1);
    vi sz(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;
        dp0[u].resize(2);
        dp1[u].resize(2);
        dp0[u][0] = inf;
        dp1[u][0] = inf;
        dp0[u][1] = 1;
        dp1[u][1] = 2;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }
            dfs(v, u);
            sz[u] += sz[v];

            int bu = sqrt(sz[u]) + 1;
            int szv = max(dp0[v].size(), dp1[v].size()) - 1;

            vi f0(bu + 1, inf), f1(bu + 1, inf);
            int limi = min(bu, (int) dp0[u].size() - 1);
            int limj = szv;
            D(i, limi, 0) {
                D(j, limj, 0) {
                    if (i + j <= bu) {
                        f0[i + j] = min(f0[i + j], dp0[u][i] + dp0[v][j] + i * j);
                        f1[i + j] = min(f1[i + j], dp1[u][i] + dp1[v][j] + 2 * i * j);
                    }
                    f0[i] = min(f0[i], dp0[u][i] + dp1[v][j]);
                    f1[i] = min(f1[i], dp1[u][i] + dp0[v][j]);
                }
            }

            dp0[u] = std::move(f0);
            dp1[u] = std::move(f1);

            dp0[v].clear();
            dp0[v].shrink_to_fit();
            dp1[v].clear();
            dp1[v].shrink_to_fit();
        }
    };

    ll ans = 1LL * n * (n + 1);
    dfs(1, 0);
    ll mn = min(ranges::min(dp0[1]), ranges::min(dp1[1]));
    ans -= mn;

    prt(ans);
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
