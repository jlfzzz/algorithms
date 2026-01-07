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
    int n;
    rd(n);

    vvp g(n + 1);
    F(i, 1, n - 1) {
        ll u, v, w;
        rd(u, v, w);
        g[u].pb(v, w);
        g[v].pb(u, w);
    }

    vl mx1(n + 1), mx2(n + 1), mx3(n + 1), sons(n + 1);

    auto dfs1 = [&](this auto &&dfs, int u, int fa) -> void {
        for (auto [v, w]: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs(v, u);

            ll len = w + mx1[v];
            if (len > mx1[u]) {
                mx3[u] = mx2[u];
                mx2[u] = mx1[u];
                mx1[u] = len;
            } else if (len > mx2[u]) {
                mx3[u] = mx2[u];
                mx2[u] = len;
            } else if (len > mx3[u]) {
                mx3[u] = len;
            }

            sons[u] = max(sons[u], sons[v]);
        }
        sons[u] = max(sons[u], mx1[u] + mx2[u]);
    };

    ll ans = 0;
    auto dfs2 = [&](this auto &&dfs, int u, int fa, ll best, ll up) -> void {
        ans = max(ans, min(sons[u], best));

        ll best1 = -inf, best2 = -inf;
        for (auto [v, w]: g[u]) {
            if (v == fa) {
                continue;
            }

            ll t = sons[v];
            if (t > best1) {
                best2 = best1;
                best1 = t;
            } else if (t > best2) {
                best2 = t;
            }
        }

        for (auto [v, w]: g[u]) {
            if (v == fa) {
                continue;
            }

            ll other = mx1[u];
            if (mx1[v] + w == mx1[u]) {
                other = mx2[u];
            }

            ll other2 = best1;
            if (sons[v] == best1) {
                other2 = best2;
            }

            ll other3;
            if (mx1[v] + w == mx1[u]) {
                other3 = mx2[u] + mx3[u];
            } else if (mx1[v] + w == mx2[u]) {
                other3 = mx1[u] + mx3[u];
            } else {
                other3 = mx1[u] + mx2[u];
            }

            ll nbest = max({best, up + other, other2, other3});

            dfs(v, u, nbest, max(other, up) + w);
        }
    };
    dfs1(1, 0);
    dfs2(1, 0, 0, 0);

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
