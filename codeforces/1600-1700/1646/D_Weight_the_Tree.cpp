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

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);

    vvi g(n + 1);
    vi deg(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
        deg[v]++;
        deg[u]++;
    }

    if (n == 2) {
        prt(2, 2);
        prt(1, 1);
        return;
    }

    vp dp1(n + 1), dp0(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs(v, u);

            dp1[u].fi += dp0[v].fi;
            dp1[u].se += dp0[v].se;

            if (dp1[v].fi > dp0[v].fi) {
                dp0[u].fi += dp1[v].fi;
                dp0[u].se += dp1[v].se;
            } else if (dp1[v].fi < dp0[v].fi) {
                dp0[u].fi += dp0[v].fi;
                dp0[u].se += dp0[v].se;
            } else {
                if (dp1[v].se < dp0[v].se) {
                    dp0[u].fi += dp1[v].fi;
                    dp0[u].se += dp1[v].se;
                } else {
                    dp0[u].fi += dp0[v].fi;
                    dp0[u].se += dp0[v].se;
                }
            }
        }

        dp1[u].fi++;
        dp1[u].se += deg[u];
        dp0[u].se++;
    };
    dfs(1, 0);

    vi weight(n + 1);
    auto dfs2 = [&](this auto &&dfs, int u, int fa, int choose) -> void {
        weight[u] = choose ? deg[u] : 1;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            if (choose) {
                dfs(v, u, 0);
            } else {
                if (dp1[v].fi > dp0[v].fi) {
                    dfs(v, u, 1);
                } else if (dp1[v].fi < dp0[v].fi) {
                    dfs(v, u, 0);
                } else {
                    if (dp1[v].se < dp0[v].se) {
                        dfs(v, u, 1);
                    } else {
                        dfs(v, u, 0);
                    }
                }
            }
        }
    };


    if (dp1[1].fi > dp0[1].fi) {
        prt(dp1[1].fi, dp1[1].se);
        dfs2(1, 0, 1);
    } else if (dp1[1].fi < dp0[1].fi) {
        prt(dp0[1].fi, dp0[1].se);
        dfs2(1, 0, 0);
    } else {
        if (dp1[1].se < dp0[1].se) {
            prt(dp1[1].fi, dp1[1].se);
            dfs2(1, 0, 1);
        } else {
            prt(dp0[1].fi, dp0[1].se);
            dfs2(1, 0, 0);
        }
    }

    prv(weight, 1);
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
