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

ll dp[N][6][3], a[N];
vector<int> g[N];
int n, k;

void dfs(int x, int fa) {
    dp[x][1][0] = a[x];
    dp[x][0][2] = 0;
    for (int v: g[x])
        if (v != fa) {
            dfs(v, x);
        }
    for (int v: g[x])
        if (v != fa) {
            for (int i = k; i >= 0; i--) {
                for (int j = 0; j <= i; j++) {
                    dp[x][i][2] = max(dp[x][i][2], dp[x][i - j][1] + max(dp[v][j + 1][0], dp[v][j + 1][1]));
                    dp[x][i][2] = max(dp[x][i][2], dp[x][i - j][2] + max({dp[v][j][0], dp[v][j][1], dp[v][j][2]}));

                    dp[x][i][1] = max(dp[x][i][1], dp[x][i - j][0] + max(dp[v][j + 1][0], dp[v][j + 1][1]));
                    dp[x][i][1] = max(dp[x][i][1], dp[x][i - j][1] + max({dp[v][j][0], dp[v][j][1], dp[v][j][2]}));

                    dp[x][i][0] = max(dp[x][i][0], dp[x][i - j][0] + max({dp[v][j][0], dp[v][j][1], dp[v][j][2]}));
                }
            }
        }
}
int main() {
    memset(dp, -0x3f, sizeof(dp));
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    ll ans = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= 2; j++) {
            ans = max(ans, dp[1][i][j]);
        }
    }
    cout << ans;

    return 0;
}
