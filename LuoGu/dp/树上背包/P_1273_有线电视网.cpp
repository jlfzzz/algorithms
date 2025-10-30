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
    int n, m;
    rd(n, m);

    vvp g(n + 1);
    F(i, 1, n - m) {
        int k;
        rd(k);
        F(j, 1, k) {
            int a, c;
            rd(a, c);
            g[i].pb(a, c);
        }
    }

    vi money(n + 1, 0);
    F(i, 1, m) {
        int w;
        rd(w);
        money[n - m + i] = w;
    }

    vector<vl> dp(n + 1);

    const long long NEG_INF = -(1LL << 60);

    function<int(int)> dfs = [&](int u) -> int {
        if (u >= n - m + 1) {
            dp[u] = vl(2, NEG_INF);
            dp[u][0] = 0;
            dp[u][1] = money[u];
            return 1;
        }

        dp[u] = vl(1, 0);
        int totalLeaves = 0;
        for (auto [v, cost]: g[u]) {
            int childLeaves = dfs(v);
            vl newDp(totalLeaves + childLeaves + 1, NEG_INF);
            for (int i = 0; i <= totalLeaves; i++) {
                for (int t = 0; t <= childLeaves; t++) {
                    long long add = dp[v][t];
                    if (t > 0)
                        add -= cost;
                    newDp[i + t] = max(newDp[i + t], dp[u][i] + add);
                }
            }
            dp[u].swap(newDp);
            totalLeaves += childLeaves;
        }
        return totalLeaves;
    };

    dfs(1);

    int ans = 0;
    for (int k = m; k >= 0; k--) {
        if ((int) dp[1].size() > k && dp[1][k] >= 0) {
            ans = k;
            break;
        }
    }
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
