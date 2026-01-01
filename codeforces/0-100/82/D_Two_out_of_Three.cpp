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

ll dp[1005][1005];

void init() {}

void solve() {
    int n;
    rd(n);

    vi a(n + 1);
    rv(a, 1);

    F(i, 0, n) F(j, 0, n) dp[i][j] = INF;
    dp[0][0] = 0;

    vvp pre(n + 2, vp(n + 2, {-1, -1}));
    vvp rec(n + 2, vp(n + 2, {0, 0}));

    F(i, 0, n) {
        F(j, 0, i) {
            if (dp[i][j] == INF)
                continue;

            vi temp;
            if (j != 0)
                temp.pb(j);

            int cur = i + 1;
            while (temp.size() < 3 && cur <= n) {
                temp.pb(cur++);
            }

            if (temp.empty())
                continue;

            if (temp.size() == 1) {
                int u = temp[0];
                ll cost = dp[i][j] + a[u];
                if (cost < dp[n][0]) {
                    dp[n][0] = cost;
                    pre[n][0] = {i, j};
                    rec[n][0] = {u, 0};
                }
            } else {
                for (int x = 0; x < SZ(temp); x++) {
                    for (int y = x + 1; y < SZ(temp); y++) {
                        int u = temp[x];
                        int v = temp[y];
                        int rem = 0;

                        if (SZ(temp) == 3) {
                            for (int k: temp)
                                if (k != u && k != v)
                                    rem = k;
                        }

                        int ni = max({u, v, rem});
                        ll cost = dp[i][j] + max(a[u], a[v]);

                        if (cost < dp[ni][rem]) {
                            dp[ni][rem] = cost;
                            pre[ni][rem] = {i, j};
                            rec[ni][rem] = {u, v};
                        }
                    }
                }
            }
        }
    }

    prt(dp[n][0]);

    vp ans;
    int curr_i = n, curr_j = 0;
    while (curr_i != 0 || curr_j != 0) {
        ans.pb(rec[curr_i][curr_j]);
        pii p = pre[curr_i][curr_j];
        curr_i = p.fi;
        curr_j = p.se;
    }
    reverse(all(ans));

    for (auto p: ans) {
        if (p.se == 0)
            cout << p.fi << "\n";
        else
            cout << p.fi << " " << p.se << "\n";
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
