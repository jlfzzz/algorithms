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
    int n, k;
    rd(n, k);

    vvl a(n, vl(n));
    F(i, 0, n - 1) {
        F(j, 0, n - 1) { rd(a[i][j]); }
    }

    vvl dis(n, vl(n));
    F(i, 0, n - 1) {
        F(j, 0, n - 1) { dis[i][j] = a[i][j]; }
    }

    // 预处理所有点对最短路
    F(p, 0, n - 1) {
        F(i, 0, n - 1) {
            F(j, 0, n - 1) {
                if (dis[i][p] + dis[p][j] < dis[i][j]) {
                    dis[i][j] = dis[i][p] + dis[p][j];
                }
            }
        }
    }

    // f[i][j][state]:
    //  固定额外点 i（可能作为 s），在包含：
    //    - 部分 {1..K} 终端（用 state 的低 K 位表示）
    //    - 以及“额外点 i”（第 K 位）
    //  的连通子图中，以 j 结尾的最小代价
    int states = 1 << (k + 1);
    vector<vvl> f(n, vvl(n, vl(states, INF)));

    // 初始状态：
    //  对每个额外点 i：
    //    - 只包含终端 j（1..K，对应 0..k-1），以 j 结尾，代价 0
    //    - 只包含额外点 i（第 K 位），以 i 结尾，代价 0
    F(i, 0, n - 1) {
        F(j, 0, k - 1) { f[i][j][1 << j] = 0; }
        f[i][i][1 << k] = 0;
    }

    // 按 state 做 Steiner DP（子集合并 + 在图上走动）
    F(state, 1, states - 1) {
        // 1) 子集划分合并：k + (state^k) = state
        F(i, 0, n - 1) {
            F(j, 0, n - 1) {
                for (int sub = (state - 1) & state; sub > 0; sub = (sub - 1) & state) {
                    int other = state ^ sub;
                    if (sub < other) {
                        continue; // 避免重复的无序划分
                    }
                    if (f[i][j][sub] == INF || f[i][j][other] == INF) {
                        continue;
                    }
                    f[i][j][state] = min(f[i][j][state], f[i][j][sub] + f[i][j][other]);
                }
            }
        }

        // 2) 在图上扩展终点 j：相当于在最短路图上做一次松弛
        F(i, 0, n - 1) {
            F(j, 0, n - 1) {
                if (f[i][j][state] == INF) {
                    continue;
                }
                F(k2, 0, n - 1) {
                    ll cand = f[i][j][state] + dis[j][k2];
                    if (cand < f[i][k2][state]) {
                        f[i][k2][state] = cand;
                    }
                }
            }
        }
    }

    int Q;
    rd(Q);
    while (Q--) {
        int s, t;
        rd(s, t);
        s--;
        t--;

        int full_state = (1 << (k + 1)) - 1;
        ll ans = f[s][t][full_state];
        prt(ans);
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
