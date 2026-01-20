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

void init() {}

void solve() {
    int n;
    rd(n);

    vi p(n);
    rv(p);

    vvi g(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    vi sz(n + 1, 0);
    auto dfs1 = [&](this auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;
        for (int v: g[u]) {
            if (v != fa) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        }
    };
    dfs1(1, 0);

    int memo[20][20];
    memset(memo, -1, sizeof(memo));

    auto dfs = [&](this auto &&dfs, int u, int fa, int offset) -> int {
        if (memo[u][offset] != -1)
            return memo[u][offset];

        vi kids;
        for (int v: g[u]) {
            if (v != fa)
                kids.pb(v);
        }
        int m = SZ(kids);

        int cur = (p[offset] == u);

        if (m == 0) {
            return memo[u][offset] = cur;
        }

        int all = 1 << m;
        vi msize(all, 0);
        for (int mask = 0; mask < all; mask++) {
            for (int i = 0; i < m; i++) {
                if ((mask >> i) & 1) {
                    msize[mask] += sz[kids[i]];
                }
            }
        }

        vi dp(all, -inf);
        dp[0] = 0;

        for (int mask = 0; mask < all; mask++) {
            if (dp[mask] == -inf)
                continue;

            int nxt = offset + 1 + msize[mask];

            for (int i = 0; i < m; i++) {
                if (!((mask >> i) & 1)) {
                    int next_mask = mask | (1 << i);
                    int val = dfs(kids[i], u, nxt);
                    dp[next_mask] = max(dp[next_mask], dp[mask] + val);
                }
            }
        }

        return memo[u][offset] = dp[all - 1] + cur;
    };

    auto get_ans = [&](this auto &&get_ans, int u, int fa, int offset) -> void {
        cout << u << " ";

        vi kids;
        for (int v: g[u]) {
            if (v != fa)
                kids.pb(v);
        }
        int m = SZ(kids);
        if (m == 0)
            return;

        int all = 1 << m;
        vi msize(all, 0);
        for (int mask = 0; mask < all; mask++) {
            for (int i = 0; i < m; i++) {
                if ((mask >> i) & 1)
                    msize[mask] += sz[kids[i]];
            }
        }

        vi dp(all, -inf);
        dp[0] = 0;
        for (int mask = 0; mask < all; mask++) {
            if (dp[mask] == -inf)
                continue;
            int nxt = offset + 1 + msize[mask];
            for (int i = 0; i < m; i++) {
                if (!((mask >> i) & 1)) {
                    int next_mask = mask | (1 << i);
                    int val = dfs(kids[i], u, nxt);
                    dp[next_mask] = max(dp[next_mask], dp[mask] + val);
                }
            }
        }

        vi order;
        int curr = all - 1;
        while (curr > 0) {
            bool found = false;
            for (int i = 0; i < m; i++) {
                if ((curr >> i) & 1) {
                    int prev = curr ^ (1 << i);
                    int child_start_pos = offset + 1 + msize[prev];

                    if (dp[prev] != -inf && dp[curr] == dp[prev] + dfs(kids[i], u, child_start_pos)) {
                        order.pb(i);
                        curr = prev;
                        found = true;
                        break;
                    }
                }
            }
        }
        reverse(all(order));

        int current_pos = offset + 1;
        for (int i: order) {
            get_ans(kids[i], u, current_pos);
            current_pos += sz[kids[i]];
        }
    };

    dfs(1, 0, 0);
    get_ans(1, 0, 0);
    cout << "\n";
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
