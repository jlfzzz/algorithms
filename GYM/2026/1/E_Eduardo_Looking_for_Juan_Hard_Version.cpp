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

int Multitest = 0;

const int LOG = 21;
int pref[N], vals[N], depth[N];
int fa[LOG][N];
vi primes;
bool prime[71];
int masks[71];

void init() {
    F(i, 2, 70) prime[i] = true;
    F(p, 2, 70) {
        if (prime[p]) {
            primes.push_back(p);
            for (int i = p * p; i <= 70; i += p)
                prime[i] = false;
        }
    }
    F(i, 1, 70) {
        int x = i;
        int m = 0;
        F(j, 0, SZ(primes) - 1) {
            int c = 0;
            while (x % primes[j] == 0) {
                x /= primes[j];
                c++;
            }
            if (c % 2 != 0)
                m |= (1 << j);
        }
        masks[i] = m;
    }
}

int dp[21][1 << 20];

void solve() {
    int n, l;
    rd(n, l);

    vi a(n + 1);
    rv(a, 1);

    vvi g(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 1;
    int u = 1 << 19;
    F(mask, 1, u - 1) {
        F(i, 0, 18) {
            if (mask >> i & 1) {
                int t = mask ^ (1 << i);
                int p = primes[i];

                F(j, 1, 19) {
                    int cur = dp[j][t];
                    if (cur == inf)
                        continue;

                    int prod = cur * p;
                    if (prod <= l) {
                        dp[j][mask] = min(dp[j][mask], (int) prod);
                    } else {
                        if (j + 1 <= 19) {
                            dp[j + 1][mask] = min(dp[j + 1][mask], p);
                        }
                    }
                }
            }
        }
    }

    F(i, 1, n) { vals[i] = masks[a[i]]; }

    auto dfs = [&](this auto &&dfs, int u, int pa, int pre) -> void {
        fa[0][u] = pa;
        pref[u] = pre ^ vals[u];
        F(i, 1, LOG - 1) { fa[i][u] = fa[i - 1][fa[i - 1][u]]; }
        for (int v: g[u]) {
            if (v == pa)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, pref[u]);
        }
    };

    dfs(1, 0, 0);

    int q;
    rd(q);
    while (q--) {
        int u, v;
        rd(u, v);
        int oldu = u, oldv = v;
        if (depth[u] < depth[v])
            swap(u, v);
        int d = depth[u] - depth[v];
        F(i, 0, LOG - 1) {
            if ((d >> i) & 1)
                u = fa[i][u];
        }
        int lca = u;
        if (u != v) {
            D(i, LOG - 1, 0) {
                if (fa[i][u] != fa[i][v]) {
                    u = fa[i][u];
                    v = fa[i][v];
                }
            }
            lca = fa[0][u];
        }

        int ans = pref[oldu] ^ pref[oldv] ^ vals[lca];

        if (ans == 0) {
            prt(0);
            continue;
        }

        F(i, 1, 19) {
            if (dp[i][ans] != inf) {
                prt(i);
                break;
            }
        }
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
