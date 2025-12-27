#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define us unsigned
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD2 = int(1e9 + 7);
constexpr int MOD = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

namespace utils {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vl a(n + 1);
    rv(a, 1);

    struct Edge {
        int u, v;
        ll val_u, val_v;
        bool operator<(const Edge &other) const { return val_v < other.val_v; }
    };

    vector<Edge> edges;

    F(i, 0, m - 1) {
        int u, v;
        rd(u, v);
        edges.pb(Edge{u, v, a[u], a[v]});
    }

    sort(all(edges));

    vector<map<ll, ll>> dp(n + 1);

    ll ans = 0;

    for (auto &[u, v, val_u, val_v]: edges) {
        ll target = val_v - val_u;
        ll ways = 1;

        if (target >= 1) {
            if (dp[u].count(target)) {
                ways = (ways + dp[u][target]) % MOD;
            }
        }

        dp[v][val_u] = (dp[v][val_u] + ways) % MOD;
        ans = (ans + ways) % MOD;
    }

    prt(ans);
}

void solve2() {
    int n, m;
    rd(n, m);

    vl a(n + 1);
    rv(a, 1);

    vp edges;

    vvp g(n + 1);

    F(i, 0, m - 1) {
        int u, v;
        rd(u, v);
        edges.pb(u, v);
        g[v].pb(a[u], i);
    }

    F(i, 1, n) { sort(all(g[i])); }

    vvl memo2(n + 1);
    F(i, 1, n) { memo2[i].assign(SZ(g[i]), -1); }

    vl memo(m, -1);
    auto dfs = [&](this auto &&dfs, int idx) -> ll {
        if (memo[idx] != -1)
            return memo[idx];

        auto [u, v] = edges[idx];
        ll target = a[v] - a[u];
        ll res = 1;

        if (target >= 1) {
            auto &vec = g[u];
            auto &sum = memo2[u];

            auto itt = lower_bound(all(vec), pii{target, -1});

            if (itt != vec.end() && itt->fi == target) {
                int pos = int(itt - vec.begin());

                if (sum[pos] != -1) {
                    res = (res + sum[pos]) % MOD;
                } else {
                    ll temp = 0;
                    for (auto it = itt; it != vec.end() && it->fi == target; it++) {
                        temp = (temp + dfs(it->se)) % MOD;
                    }
                    sum[pos] = temp;
                    res = (res + temp) % MOD;
                }
            }
        }

        return memo[idx] = res;
    };

    ll ans = 0;
    F(i, 0, m - 1) { ans = (ans + dfs(i)) % MOD; }

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
