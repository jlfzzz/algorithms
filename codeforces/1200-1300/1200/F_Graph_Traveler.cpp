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

    vl a(n + 1);
    rv(a, 1);

    vi m(n + 1);
    vvi g(n + 1);

    F(i, 1, n) {
        int t;
        rd(t);
        m[i] = t;
        F(j, 1, t) {
            int v;
            rd(v);
            g[i].pb(v);
        }
    }

    int q;
    rd(q);

    static const int M = 2520;

    vi kmod(n + 1);
    F(i, 1, n) {
        long long x = a[i] % M;
        if (x < 0)
            x += M;
        kmod[i] = (int) x;
    }

    vvl dp(n + 1, vl(M, 0));
    vvi vis(n + 1, vi(M, 0));

    vvi nextV(n + 1, vi(M));
    vvi nextR(n + 1, vi(M));

    F(v, 1, n) {
        F(r, 0, M - 1) {
            int r2 = r + kmod[v];
            if (r2 >= M)
                r2 -= M;

            int x = r2 % m[v];
            int u = g[v][x];

            nextV[v][r] = u;
            nextR[v][r] = r2;
        }
    }

    vi lastSeen(n + 1, 0);
    int curMark = 0;

    F(v, 1, n) {
        F(r, 0, M - 1) {
            if (vis[v][r] != 0)
                continue;

            vector<pair<int, int>> path;
            int cv = v, cr = r;

            while (true) {
                vis[cv][cr] = 1;
                path.emplace_back(cv, cr);

                int nv = nextV[cv][cr];
                int nr = nextR[cv][cr];

                if (vis[nv][nr] == 0) {
                    cv = nv;
                    cr = nr;
                    continue;
                }

                if (vis[nv][nr] == 1) {
                    int idx = 0;
                    while (!(path[idx].first == nv && path[idx].second == nr)) {
                        idx++;
                    }

                    curMark++;
                    int cnt = 0;
                    for (int i = idx; i < (int) path.size(); i++) {
                        int vv = path[i].first;
                        if (lastSeen[vv] != curMark) {
                            lastSeen[vv] = curMark;
                            cnt++;
                        }
                    }

                    for (int i = idx; i < (int) path.size(); i++) {
                        auto [vv, rr] = path[i];
                        dp[vv][rr] = cnt;
                    }

                    for (int i = idx - 1; i >= 0; i--) {
                        auto [vv, rr] = path[i];
                        int tv = nextV[vv][rr];
                        int tr = nextR[vv][rr];
                        dp[vv][rr] = dp[tv][tr];
                    }

                } else {
                    for (int i = (int) path.size() - 1; i >= 0; i--) {
                        auto [vv, rr] = path[i];
                        int tv = nextV[vv][rr];
                        int tr = nextR[vv][rr];
                        dp[vv][rr] = dp[tv][tr];
                    }
                }

                for (auto [vv, rr]: path) {
                    vis[vv][rr] = 2;
                }

                break;
            }
        }
    }

    while (q--) {
        ll x, y;
        rd(x, y);

        ll r0 = y % M;
        if (r0 < 0)
            r0 += M;

        cout << dp[(int) x][(int) r0] << '\n';
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
