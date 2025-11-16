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
    int n, m, k;
    rd(n, m, k);
    string s;
    rd(s);
    string t = " " + s;
    const int NEG_INF = -1000000000;
    vector<int> a(n + 2, 0);
    a[1] = 1;
    for (int i = 2; i <= n; i++) {
        a[i] = (t[i] != t[i - 1]) ? 1 : 0;
    }
    vector<vector<int>> g(k + 1, vector<int>(m + 1, NEG_INF));
    g[0][0] = 0;
    for (int i = 1; i <= k; i++) {
        vector<int> pos;
        for (int x = i; x <= n + 1; x += k) {
            pos.push_back(x);
        }
        int cnt = (int) pos.size();
        if (cnt == 0) {
            for (int p = 0; p <= m; p++) {
                g[i][p] = max(g[i][p], g[i - 1][p]);
            }
            continue;
        }
        vector<vector<array<int, 2>>> f(cnt + 1, vector<array<int, 2>>(m + 1));
        for (int j = 0; j <= cnt; j++) {
            for (int u = 0; u <= m; u++) {
                f[j][u][0] = NEG_INF;
                f[j][u][1] = NEG_INF;
            }
        }
        f[1][0][0] = a[pos[0]];
        for (int j = 1; j < cnt; j++) {
            for (int used = 0; used <= min(m, j); used++) {
                for (int p_prev = 0; p_prev <= 1; p_prev++) {
                    int w = f[j][used][p_prev];
                    if (w <= NEG_INF / 2) {
                        continue;
                    }
                    int cur_pos = pos[j - 1];
                    int nxt_pos = pos[j];
                    int x = (cur_pos == 1 ? 1 : (a[cur_pos] ^ p_prev));
                    int y = (nxt_pos == n + 1 ? 0 : a[nxt_pos]);
                    if (f[j + 1][used][0] < w + y) {
                        f[j + 1][used][0] = w + y;
                    }
                    if (used + 1 <= m) {
                        int xx = (cur_pos == 1 ? 1 : (x ^ 1));
                        int yy = (nxt_pos == n + 1 ? 0 : (y ^ 1));
                        int val = w + (xx - x) + yy;
                        if (f[j + 1][used + 1][1] < val) {
                            f[j + 1][used + 1][1] = val;
                        }
                    }
                }
            }
        }
        for (int used = 0; used <= min(cnt, m); used++) {
            for (int last = 0; last < 2; last++) {
                int best_val = f[cnt][used][last];
                if (best_val <= NEG_INF / 2) {
                    continue;
                }
                for (int p = used; p <= m; p++) {
                    if (g[i][p] < g[i - 1][p - used] + best_val) {
                        g[i][p] = g[i - 1][p - used] + best_val;
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int p = 0; p <= m; p++) {
        if (ans < g[k][p]) {
            ans = g[k][p];
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
