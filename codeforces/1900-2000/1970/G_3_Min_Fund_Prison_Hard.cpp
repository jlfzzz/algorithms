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
    int n, m, c;
    rd(n, m, c);

    struct E {
        int to, id;
    };
    vector<vector<E>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    vector<int> dfn(n + 1), low(n + 1);
    int ts = 0;
    vector<pii> bridges;
    vector<int> sz(n + 1), blockId(n + 1);
    int bid = 0;
    map<int, int> blockSz;
    auto tarjan = [&](this auto &&tarjan, int u, int pe) -> void {
        dfn[u] = low[u] = ++ts;
        blockId[u] = bid;
        sz[u] = 1;
        for (auto e: g[u]) {
            if (e.id == pe)
                continue;
            int v = e.to;
            if (!dfn[v]) {
                tarjan(v, e.id);
                low[u] = min(low[u], low[v]);
                sz[u] += sz[v];
                if (low[v] > dfn[u]) {
                    bridges.emplace_back(u, v);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, -1);
            blockSz[bid] = sz[i];
            bid++;
        }
    }

    int ans = inf;

    constexpr int MAXW = 60000 + 5;
    int W = (int) (n / 2 + 1);

    vector<int> compSize(bid);
    for (int i = 0; i < bid; ++i)
        compSize[i] = blockSz[i];
    vector<vector<int>> compSplits(bid);
    for (auto &[a, b]: bridges) {
        int block = blockId[a];
        int s1 = sz[b];
        int s2 = compSize[block] - s1;
        compSplits[block].push_back(min(s1, s2));
    }

    static bitset<MAXW> F, G;
    F.reset();
    G.reset();
    G[0] = true;

    for (int i = 0; i < bid; ++i) {
        int S = compSize[i];
        for (int s: compSplits[i]) {
            if (s <= W)
                F |= (G << s);
            int t = S - s;
            if (t <= W)
                F |= (G << t);
        }
        if (S <= W)
            G |= (G << S);
    }

    F |= G;

    for (int i = W; i >= 1; --i) {
        if (F.test(i)) {
            ans = min(ans, i * i + (n - i) * (n - i));
        }
    }

    if (ans == inf) {
        prt(-1);
        return;
    }

    ans += c * (bid - 1);
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
