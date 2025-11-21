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
    int n, m;
    rd(n, m);

    vvp g(n + 1);
    F(i, 1, n - 1) {
        int u, v, w;
        rd(u, v, w);
        g[u].pb(v, w);
        g[v].pb(u, w);
    }

    vi qs(m + 1);
    vector<bool> ok(m + 1, false);
    F(i, 1, m) rd(qs[i]);

    vi sz(n + 1), son(n + 1);
    vl dis(n + 1);

    auto dfs_sz = [&](auto &&self, int u, int fa, ll d) -> void {
        sz[u] = 1;
        dis[u] = d;
        son[u] = 0;
        for (auto &ed: g[u]) {
            int v = ed.fi;
            ll w = ed.se;
            if (v == fa)
                continue;
            self(self, v, u, d + w);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]])
                son[u] = v;
        }
    };
    dfs_sz(dfs_sz, 1, 0, 0);

    auto dfs_dsu = [&](auto &&self, int u, int fa) -> set<ll> * {
        set<ll> *S;

        if (son[u]) {
            S = self(self, son[u], u);
        } else {
            S = new set<ll>();
        }

        F(i, 1, m) {
            if (ok[i])
                continue;
            if (S->count(qs[i] + dis[u]))
                ok[i] = true;
        }

        for (auto &ed: g[u]) {
            int v = ed.fi;
            if (v == fa || v == son[u])
                continue;

            set<ll> *sub = self(self, v, u);

            for (ll x_dist: *sub) {
                F(i, 1, m) {
                    if (ok[i])
                        continue;

                    ll target_y = (ll) qs[i] + 2 * dis[u] - x_dist;
                    if (S->count(target_y))
                        ok[i] = true;

                    if (x_dist - dis[u] == qs[i])
                        ok[i] = true;
                }
            }

            for (ll x_dist: *sub) {
                S->insert(x_dist);
            }
            delete sub;
        }

        S->insert(dis[u]);
        return S;
    };

    set<ll> *root_set = dfs_dsu(dfs_dsu, 1, 0);
    delete root_set;

    F(i, 1, m) {
        if (ok[i])
            prt("AYE");
        else
            prt("NAY");
    }
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
