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
#define F first
#define S second
int n, dp[N][2];
pair<pair<int, int>, pair<int, int>> pre[N][2];
void print(int x, int t) {
    if (pre[x][t].F.F == -1) {
        cout << x;
        return;
    }
    if (t == 0 && pre[x][t].F.S == 1)
        cout << "(";
    print(pre[x][t].F.F, pre[x][t].F.S);
    if (t == 0 && pre[x][t].F.S == 1)
        cout << ")";
    cout << (t ? "+" : "*");
    if (t == 0 && pre[x][t].S.S == 1)
        cout << "(";
    print(pre[x][t].S.F, pre[x][t].S.S);
    if (t == 0 && pre[x][t].S.S == 1)
        cout << ")";
}
int main() {
    cin >> n;
    memset(dp, 63, sizeof(dp));
    dp[1][0] = 1, dp[11][0] = 2, dp[111][0] = 3, dp[1111][0] = 4;
    pre[1][0] = pre[11][0] = pre[111][0] = pre[1111][0] = make_pair(make_pair(-1, -1), make_pair(-1, -1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++)
            if (i % j == 0) {
                int x = j, y = i / j;
                for (int c0 = 0; c0 < 2; c0++)
                    for (int c1 = 0; c1 < 2; c1++) {
                        if (dp[i][0] > dp[x][c0] + (c0 ? 2 : 0) + dp[y][c1] + (c1 ? 2 : 0) + 1) {
                            dp[i][0] = dp[x][c0] + (c0 ? 2 : 0) + dp[y][c1] + (c1 ? 2 : 0) + 1;
                            pre[i][0] = make_pair(make_pair(x, c0), make_pair(y, c1));
                        }
                    }
            }
        for (int j = 1; j < i; j++) {
            int x = j, y = i - j;
            for (int c0 = 0; c0 < 2; c0++)
                for (int c1 = 0; c1 < 2; c1++) {
                    if (dp[i][1] > dp[x][c0] + dp[y][c1] + 1) {
                        dp[i][1] = dp[x][c0] + dp[y][c1] + 1;
                        pre[i][1] = make_pair(make_pair(x, c0), make_pair(y, c1));
                    }
                }
        }
    }
    if (dp[n][0] < dp[n][1])
        print(n, 0);
    else
        print(n, 1);
    return 0;
}
