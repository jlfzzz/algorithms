#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
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
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, k;
    rd(n, k);

    vvp g(n + 1);
    F(i, 1, n - 1) {
        ll u, v, w;
        rd(u, v, w);
        g[u].pb(v, w);
        g[v].pb(u, w);
    }

    vi kkk(n + 1);
    F(i, 1, k) {
        int t;
        rd(t);
        kkk[t] = 1;
    }

    vl sz(n + 1, 0);
    vl d1(n + 1, -INF), d2(n + 1, -INF), up(n + 1, -INF);
    ll cur_total = 0;
    auto dfs1 = [&](this auto &&dfs, int u, int fa) -> void {
        if (kkk[u]) {
            sz[u] = 1;
            d1[u] = 0;
        }

        for (auto [v, w]: g[u]) {
            if (v == fa)
                continue;

            dfs(v, u);

            sz[u] += sz[v];

            if (sz[v] > 0) {
                cur_total += 2 * w;
            }

            if (d1[v] != -INF) {
                ll dist = d1[v] + w;
                if (dist > d1[u]) {
                    d2[u] = d1[u];
                    d1[u] = dist;
                } else if (dist > d2[u]) {
                    d2[u] = dist;
                }
            }
        }
    };

    dfs1(1, 0);

    vl ans(n + 1);

    auto dfs2 = [&](this auto &&dfs, int u, int fa) -> void {
        ll max_d = max(d1[u], up[u]);
        if (max_d < 0)
            max_d = 0;
        ans[u] = cur_total - max_d;

        for (auto [v, w]: g[u]) {
            if (v == fa)
                continue;

            ll from_u = up[u];
            if (d1[v] != -INF && d1[u] == d1[v] + w) {
                from_u = max(from_u, d2[u]);
            } else {
                from_u = max(from_u, d1[u]);
            }

            if (from_u != -INF)
                up[v] = from_u + w;
            else if (kkk[u])
                up[v] = w;
            else
                up[v] = -INF;


            ll old_total = cur_total;
            if (sz[v] == k)
                cur_total -= 2 * w;
            else if (sz[v] == 0)
                cur_total += 2 * w;

            dfs(v, u);

            cur_total = old_total;
        }
    };

    dfs2(1, 0);

    F(i, 1, n) { prt(ans[i]); }
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
