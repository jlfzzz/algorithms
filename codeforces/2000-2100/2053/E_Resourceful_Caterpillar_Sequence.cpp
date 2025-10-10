#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
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

namespace utils {
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

    struct range : ranges::view_base {
        struct Iterator {
            using iterator_category = random_access_iterator_tag;
            using value_type = long long;
            using difference_type = ptrdiff_t;
            ll val, d;
            Iterator() = default;
            Iterator(ll val, ll d) : val(val), d(d) {};
            value_type operator*() const { return val; }
            Iterator &operator++() { return val += d, *this; }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            Iterator &operator--() { return val -= d, *this; }
            Iterator operator--(int) {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }
            difference_type operator-(const Iterator &other) const { return (val - other.val) / d; }
            bool operator==(const Iterator &other) const { return val == other.val; }
        };
        Iterator Begin, End;
        explicit range(ll n) : Begin(0, 1), End(max(n, ll{0}), 1) {};
        range(ll a, ll b, ll d = ll(1)) : Begin(a, d), End(b, d) {
            ll cnt = b == a or (b - a > 0) != (d > 0) ? 0 : (b - a) / d + bool((b - a) % d);
            End.val = a + max(cnt, ll(0)) * d;
        };
        [[nodiscard]] Iterator begin() const { return Begin; }
        [[nodiscard]] Iterator end() const { return End; };
        [[nodiscard]] ptrdiff_t size() const { return End - Begin; }
    };
} // namespace utils

using namespace utils;

#define int ll

int Multitest = 1;

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

    // 参考思路实现：vis 标记 + 子树和 + 子/父方向统计
    vector<int> deg(n + 1), vis(n + 1);
    for (int i = 1; i <= n; i++)
        deg[i] = (int) g[i].size();
    int leaf_cnt = 0;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1) {
            leaf_cnt++;
            vis[i] = 1; // 叶子本身标 1
        }
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1) {
            for (int v: g[i])
                vis[v] = 1; // 邻居也标 1
        }

    long long ans = leaf_cnt * (n - leaf_cnt);

    vector<int> parent(n + 1), sz(n + 1), sum(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        parent[u] = fa;
        sz[u] = 1;
        sum[u] = vis[u];
        for (int v: g[u])
            if (v != fa) {
                dfs(v, u);
                sum[u] += sum[v];
                sz[u] += sz[v];
            }
    };
    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1)
            continue; // 情况1已经计过
        long long tot1 = 0, tot2 = 0;
        // 子方向：挑子节点 k，要求 k 与叶子相邻、且 k 不是叶子
        for (int j: g[i]) {
            if (j == parent[i])
                continue;
            if (vis[j] == 0)
                continue;
            if (deg[j] == 1)
                continue;
            tot1 += (sz[j] - sum[j]);
        }
        // 父方向：父亲满足要求
        if (i != 1 && vis[parent[i]] && deg[parent[i]] > 1) {
            tot2 += (n - sz[i]) - (sum[1] - sum[i]);
        }
        ans += tot1 + tot2;
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
