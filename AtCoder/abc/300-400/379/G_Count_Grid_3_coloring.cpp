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
    int H, W;
    rd(H, W);
    vector<string> S(H);
    rv(S);

    if (H < W) {
        vector<string> T(W, string(H, ' '));
        for (int r = 0; r < H; ++r) {
            for (int c = 0; c < W; ++c) {
                T[c][r] = S[r][c];
            }
        }
        S = T;
        swap(H, W);
    }

    int max_mask = 1;
    vector<int> p3(W + 1);
    p3[0] = 1;
    for (int i = 0; i < W; ++i) {
        max_mask *= 3;
        p3[i + 1] = p3[i] * 3;
    }

    vector<int> dp(max_mask, 0);
    vector<int> next_dp(max_mask, 0);
    vector<int> active;

    dp[0] = 1;
    active.pb(0);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            vector<int> next_active;
            if (!active.empty())
                next_active.reserve(active.size() * 2);

            int fixed = -1;
            if (S[i][j] != '?')
                fixed = S[i][j] - '1';

            for (int mask: active) {
                int count = dp[mask];
                if (count == 0)
                    continue;
                dp[mask] = 0;

                int u = (mask / p3[j]) % 3;
                int l = (j > 0) ? (mask / p3[j - 1]) % 3 : -1;

                for (int c = 0; c < 3; ++c) {
                    if (fixed != -1 && c != fixed)
                        continue;
                    if (i > 0 && c == u)
                        continue;
                    if (j > 0 && c == l)
                        continue;

                    int nxt_mask = mask + (c - u) * p3[j];

                    if (next_dp[nxt_mask] == 0) {
                        next_active.pb(nxt_mask);
                    }

                    next_dp[nxt_mask] += count;
                    if (next_dp[nxt_mask] >= MOD)
                        next_dp[nxt_mask] -= MOD;
                }
            }
            active = next_active;
            swap(dp, next_dp);
        }
    }

    ll ans = 0;
    for (int mask: active) {
        ans = (ans + dp[mask]) % MOD;
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
