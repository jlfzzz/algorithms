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

    vvi g(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    vi vis(n + 1);
    vp ans;

    auto bfs = [&](int start, int st) -> void {
        queue<pii> q;
        q.ep(start, st);

        while (!q.empty()) {
            auto [u, d] = q.front();
            q.pop();

            for (int v: g[u]) {
                if (!vis[v]) {
                    vis[v] = 1;
                    if (d == 0) {
                        ans.pb(v, u);
                    } else {
                        ans.pb(u, v);
                    }
                    q.ep(v, d ^ 1);
                }
            }
        }
    };

    F(i, 1, n) {
        if (SZ(g[i]) == 2) {
            int u = g[i][0];
            int v = g[i][1];

            vis[u] = vis[v] = vis[i] = 1;
            ans.pb(u, i);
            ans.pb(i, v);

            bfs(u, 1);
            bfs(v, 0);

            prt("YES");
            for (auto [x, y]: ans) {
                prt(x, y);
            }

            return;
        }
    }

    prt("NO");

    // vi parent(n + 1);
    // auto dfs1 = [&](this auto &&dfs, int u, int fa) -> void {
    //     parent[u] = fa;
    //     for (int v: g[u]) {
    //         if (v != fa) {
    //             dfs(v, u);
    //         }
    //     }
    // };

    // dfs1(1, 0);

    // vi vis(n + 1);
    // vp ans;
    // F(i, 1, n) {
    //     auto bfs = [&](int start) -> void {
    //         queue<pii> q;
    //         q.ep(start, 0);

    //         while (!q.empty()) {
    //             auto [u, d] = q.front();
    //             q.pop();

    //             for (int v: g[u]) {
    //                 if (!vis[v]) {
    //                     vis[v] = 1;
    //                     if (d == 0) {
    //                         ans.pb(v, u);
    //                     } else {
    //                         ans.pb(u, v);
    //                     }
    //                     q.ep(v, d ^ 1);
    //                 }
    //             }
    //         }
    //     };

    //     if (SZ(g[i]) == 1) {
    //         if (i == 1) {
    //             int son = g[i][0];
    //             if (SZ(g[son]) == 2) {
    //                 vis[1] = vis[son] = 1;
    //                 int nxt = g[son][0];
    //                 if (nxt == 1) {
    //                     nxt = g[son][1];
    //                 }

    //                 vis[nxt] = 1;
    //                 ans.pb(1, son);
    //                 ans.pb(son, nxt);
    //                 bfs(nxt);


    //                 prt("YES");
    //                 for (auto [x, y]: ans) {
    //                     prt(x, y);
    //                 }
    //                 return;
    //             }
    //         } else {
    //             int fa = parent[i];
    //             if (SZ(g[fa]) == 2) {
    //                 if (fa == 1) {
    //                     int nxt = g[fa][0];
    //                     if (nxt == i) {
    //                         nxt = g[fa][1];
    //                     }

    //                     vis[i] = vis[fa] = vis[nxt] = 1;
    //                     ans.pb(i, fa);
    //                     ans.pb(fa, nxt);
    //                     bfs(nxt);
    //                 } else {
    //                     int nxt = parent[fa];

    //                     vis[i] = vis[fa] = vis[nxt] = 1;
    //                     ans.pb(i, fa);
    //                     ans.pb(fa, nxt);
    //                     bfs(nxt);
    //                 }

    //                 prt("YES");
    //                 for (auto [x, y]: ans) {
    //                     prt(x, y);
    //                 }
    //                 return;
    //             }
    //         }
    //     }
    // }

    // prt("NO");
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
