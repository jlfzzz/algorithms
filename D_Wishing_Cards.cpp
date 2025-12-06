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

constexpr int KMAX = 360;
static ll dp[KMAX + 5][KMAX + 5];
static ll ndp[KMAX + 5][KMAX + 5];
static ll bestv[KMAX + 5][KMAX + 5];

int Multitest = 1;

void init() {}

void solve() {
    ll n, k;
    rd(n, k);

    vl a(n + 1);
    rv(a, 1);

    // 只保留 a[i] 成为新的前缀最大值的位置
    vector<int> pos;
    vl cap;
    pos.reserve(k + 5);
    cap.reserve(k + 5);

    ll pre = 0;
    F(i, 1, n) {
        if (a[i] > pre) {
            pre = a[i];
            if (pre > 0) { // a[i] == 0 的位置不会贡献正快乐，可直接忽略
                pos.pb(i);
                cap.pb(pre);
            }
        }
    }

    if (pos.empty() || k == 0) {
        prt(0);
        return;
    }

    pos.pb((int) n + 1); // 哨兵，方便算最后一段长度
    int m = SZ(pos) - 1;
    int KK = (int) k;
    const ll NEG = -INF;

    // dp[u][M] = 用了 u 张卡，当前最大值为 M 时的最大快乐
    F(u, 0, KK) { F(M, 0, KK) dp[u][M] = NEG; }
    dp[0][0] = 0;
    int lim = 0; // 当前可能出现的最大 M 上界

    F(t, 0, m - 1) {
        int len = pos[t + 1] - pos[t];
        int c = (int) min(cap[t], (ll) KK); // 本段能把最大值抬到的上限
        int new_lim = c;

        // 初始化 ndp
        F(u, 0, KK) { F(M, 0, new_lim) ndp[u][M] = NEG; }

        // 预处理 bestv[u][M] = max(dp[u][0..M])
        F(u, 0, KK) {
            ll cur = NEG;
            F(M, 0, lim) {
                if (dp[u][M] > cur)
                    cur = dp[u][M];
                bestv[u][M] = cur;
            }
        }

        // 情况 1：不涨最大值，整段用旧的 M
        F(u, 0, KK) {
            F(M, 0, lim) {
                ll val = dp[u][M];
                if (val == NEG)
                    continue;
                ll nv = val + 1ll * M * len;
                if (nv > ndp[u][M])
                    ndp[u][M] = nv;
            }
        }

        // 情况 2：在这一段一开始用当前这个前缀最大朋友把最大值抬到 Mnew
        F(u, 0, KK) {
            if (lim < 0)
                continue; // 理论上不会发生
            ll allbest = bestv[u][lim]; // 这一行如果是 NEG，说明 u 这个用卡数根本无解
            if (allbest == NEG)
                continue;

            F(Mnew, 1, c) {
                if (u + Mnew > KK)
                    break;
                ll prevBest;
                if (Mnew - 1 <= lim)
                    prevBest = bestv[u][Mnew - 1];
                else
                    prevBest = allbest; // Mnew-1 已经超过旧 lim，只能用到 lim 为止的整体最大值

                if (prevBest == NEG)
                    continue;
                ll nv = prevBest + 1ll * Mnew * len;
                if (nv > ndp[u + Mnew][Mnew])
                    ndp[u + Mnew][Mnew] = nv;
            }
        }

        // 写回 dp，并把 M > new_lim 的清成 NEG
        F(u, 0, KK) {
            F(M, 0, new_lim) dp[u][M] = ndp[u][M];
            F(M, new_lim + 1, KK) dp[u][M] = NEG;
        }
        lim = new_lim;
    }

    ll ans = 0;
    F(u, 0, KK) {
        F(M, 0, lim) {
            if (dp[u][M] > ans)
                ans = dp[u][M];
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
