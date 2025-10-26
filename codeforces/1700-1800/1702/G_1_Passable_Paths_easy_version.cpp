#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define ld long double
#define db double
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

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

class LcaBinaryLifting {
public:
    vector<int> depth;
    vector<ll> dis;
    vector<vector<int>> pa;
    vector<vector<pair<int, int>>> g;
    int N, LOG;

    LcaBinaryLifting(int n, vector<vector<int>> &edges) {
        N = n;
        LOG = bit_width((unsigned) (N + 1));
        g.assign(N + 1, {});
        for (auto &e: edges) {
            int x = e[0], y = e[1], w = e[2];
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }
        depth.assign(N + 1, 0);
        dis.assign(N + 1, 0);
        pa.assign(N + 1, vector<int>(LOG, -1));

        dfs(1, -1);

        for (int j = 0; j + 1 < LOG; ++j) {
            for (int v = 1; v <= N; ++v) {
                if (pa[v][j] != -1)
                    pa[v][j + 1] = pa[pa[v][j]][j];
            }
        }
    }

    void dfs(int x, int fa) {
        pa[x][0] = fa;
        for (auto &ew: g[x]) {
            int y = ew.first, w = ew.second;
            if (y == fa)
                continue;
            depth[y] = depth[x] + 1;
            dis[y] = dis[x] + w;
            dfs(y, x);
        }
    }

    int get_kth_ancestor(int node, int k) {
        for (int i = 0; i < LOG && node != -1; ++i) {
            if (k >> i & 1) {
                node = pa[node][i];
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] > depth[y])
            swap(x, y);
        y = get_kth_ancestor(y, depth[y] - depth[x]);
        if (x == y)
            return x;
        for (int i = LOG - 1; i >= 0; --i) {
            if (pa[x][i] != pa[y][i]) {
                x = pa[x][i];
                y = pa[y][i];
            }
        }
        return pa[x][0];
    }

    ll get_dis(int x, int y) {
        int l = get_lca(x, y);
        return dis[x] + dis[y] - 2 * dis[l];
    }
};

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);

    vvi edges(n - 1);
    for (int i: range(n - 1)) {
        int u, v;
        rd(u, v);
        edges[i] = {u, v, 1};
    }

    LcaBinaryLifting lca(n, edges);

    vi dfn(n + 1);
    int ts = 0;
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        dfn[u] = ++ts;
        for (auto [v, w]: lca.g[u]) {
            if (v == fa) {
                continue;
            }
            dfs(v, u);
        }
    };
    dfs(1, 0);

    int q;
    rd(q);
    while (q--) {
        int k;
        rd(k);

        vi temp(k);
        rv(temp);

        if (k <= 2) {
            prt("YES");
            continue;
        }


        ranges::sort(temp, [&](int a, int b) { return dfn[a] < dfn[b]; });

        int sum = 0;
        for (int i = 0; i < k; ++i) {
            int a = temp[i];
            int b = temp[(i + 1) % k];
            sum += lca.get_dis(a, b);
        }

        int start = temp[0];
        int far1 = start;
        int best = -1;
        for (int x: temp) {
            int d = lca.get_dis(start, x);
            if (d > best) {
                best = d;
                far1 = x;
            }
        }
        int far2 = far1;
        best = -1;
        for (int x: temp) {
            int d = lca.get_dis(far1, x);
            if (d > best) {
                best = d;
                far2 = x;
            }
        }

        prt(sum == best * 2 ? "YES" : "NO");
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
