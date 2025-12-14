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

    vvp adj(n + 1);
    F(i, 1, n - 1) {
        ll a, b, c;
        rd(a, b, c);
        adj[a].pb(b, c);
        adj[b].pb(a, c);
    }

    vl f0(n + 1), f1(n + 1, -INF);
    auto dfs1 = [&](this auto &&dfs1, int u, int fa) -> void {
        ll sum = 0;
        ll best = -INF;
        for (auto [v, w]: adj[u]) {
            if (v == fa) {
                continue;
            }
            dfs1(v, u);
            ll base = max(f0[v], f1[v] == -INF ? -INF : f1[v] + w);
            sum += base;
            ll cand = f0[v] + w - base;
            if (cand > best) {
                best = cand;
            }
        }
        f0[u] = sum;
        if (best != -INF) {
            f1[u] = sum + best;
        }
    };

    vl g0(n + 1, -INF);
    auto dfs2 = [&](this auto &&dfs2, int u, int fa, ll k0, ll k1, ll wfa) -> void {
        ll parent_contrib = 0;
        ll parent_delta = -INF;
        if (fa != 0) {
            parent_contrib = max(k0, k1 == -INF ? -INF : k1 + wfa);
            parent_delta = k0 + wfa - parent_contrib;
        }

        ll sum = parent_contrib;
        ll top1 = -INF, top2 = -INF;
        int who = -1;

        for (auto [v, w]: adj[u]) {
            if (v == fa) {
                continue;
            }
            ll base = max(f0[v], f1[v] == -INF ? -INF : f1[v] + w);
            sum += base;
            ll d = f0[v] + w - base;
            if (d > top1) {
                top2 = top1;
                top1 = d;
                who = v;
            } else if (d > top2) {
                top2 = d;
            }
        }

        g0[u] = sum;

        for (auto [v, w]: adj[u]) {
            if (v == fa) {
                continue;
            }
            ll base = max(f0[v], f1[v] == -INF ? -INF : f1[v] + w);
            ll nk0 = sum - base;

            ll best_excl = parent_delta;
            ll use = top1;
            if (who == v) {
                use = top2;
            }
            if (use > best_excl) {
                best_excl = use;
            }

            ll nk1 = -INF;
            if (best_excl != -INF) {
                nk1 = nk0 + best_excl;
            }

            dfs2(v, u, nk0, nk1, w);
        }
    };

    dfs1(1, 0);
    dfs2(1, 0, 0, -INF, 0);

    ll ans = 0;
    F(i, 1, n) {
        if (g0[i] > ans) {
            ans = g0[i];
        }
    }
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
