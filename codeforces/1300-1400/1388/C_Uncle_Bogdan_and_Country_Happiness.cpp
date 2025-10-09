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

void solve() {
    int n, m;
    rd(n, m);

    vector<int> people(n + 1);
    rd_vec(people, 1);

    vector<int> happy(n + 1);
    rd_vec(happy, 1);

    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        rd(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> sz(n + 1);
    bool ans = true;

    auto dfs = [&](auto &&self, int u, int fa) -> pair<int, int> {
        int total = people[u];
        int good_sum = 0, bad_sum = 0;

        for (int v: g[u]) {
            if (v == fa)
                continue;
            auto [good_v, bad_v] = self(self, v, u);
            good_sum += good_v;
            bad_sum += bad_v;
            total += sz[v];
        }

        sz[u] = total;

        if ((total + happy[u]) % 2 != 0) {
            ans = false;
            return {0, 0};
        }
        int good = (total + happy[u]) / 2;
        int bad = total - good;

        if (good < 0 || bad < 0) {
            ans = false;
            return {0, 0};
        }
        if (good < good_sum) {
            ans = false;
            return {0, 0};
        }

        return make_pair(good, bad);
    };

    dfs(dfs, 1, 0);

    if (ans) {
        prt("YES");
    } else {
        prt("NO");
    }
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
