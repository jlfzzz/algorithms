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

const int N = 1e5 + 5;

vector<int> g[N];
int sz[N];

void dfs(int u, int parent) {
    sz[u] = 1;
    for (int v: g[u]) {
        if (v == parent)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        g[i].clear();

    vector<pair<int, int>> edges(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        edges[i] = {u, v};
    }

    dfs(1, 0);

    vector<int> contrib;
    for (auto [u, v]: edges) {
        if (sz[u] < sz[v])
            swap(u, v);
        contrib.push_back(sz[v] * (n - sz[v]));
    }

    int m;
    cin >> m;
    vector<int> primes(m);
    for (int i = 0; i < m; i++)
        cin >> primes[i];

    sort(contrib.rbegin(), contrib.rend());
    sort(primes.rbegin(), primes.rend());

    vector<int> edge_val(n - 1, 1);

    int idx = 0;
    if (m >= n - 1) {
        int extra = m - (n - 1) + 1;
        for (int i = 0; i < extra; i++) {
            edge_val[0] = (edge_val[0] * primes[idx]) % MOD;
            idx++;
        }
        for (int i = 1; i < n - 1; i++) {
            if (idx < m) {
                edge_val[i] = (edge_val[i] * primes[idx]) % MOD;
                idx++;
            }
        }
    } else {
        for (int i = 0; i < m; i++) {
            edge_val[i] = (edge_val[i] * primes[idx]) % MOD;
            idx++;
        }
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        ans = (ans + contrib[i] % MOD * edge_val[i] % MOD) % MOD;
    }

    cout << ans << "\n";
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
