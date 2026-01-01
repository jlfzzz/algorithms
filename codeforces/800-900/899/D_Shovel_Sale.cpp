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

ll pow10[10];
void init() {
    pow10[0] = 1;
    F(i, 1, 9) { pow10[i] = pow10[i - 1] * 10; }
}

ll dp[2][2][2][2][10];

void solve() {
    int n;
    rd(n);

    string s = to_string(n);
    int m = SZ(s);

    if (m == 1 && s[0] <= '4') {
        prt(n * (n - 1) / 2);
        return;
    }

    memset(dp, -1, sizeof(dp));
    auto dfs = [&](this auto &&dfs, int i, int hi1, int hi2, int s1, int s2) -> ll {
        if (i == m) {
            return 1;
        }

        if (!hi1 && !hi2 && !s1 && !s2) {
            return pow10[m - i];
        }

        ll &memo = dp[hi1][hi2][s1][s2][i];
        if (memo != -1) {
            return memo;
        }

        int r1 = hi1 ? s[i] - '0' : 9;
        int r2 = hi2 ? s[i] - '0' : 9;

        int ll1 = 0, ll2 = 0;
        if (s1 && i == m - 1) {
            ll1 = 1;
        }
        if (s2 && i == m - 1) {
            ll2 = 1;
        }

        ll res = 0;
        F(l1, ll1, r1) {
            F(l2, ll2, r2) {
                if (i == 0) {
                    if (s[0] - '0' <= 4) {
                        int nhi1 = hi1 && (l1 == r1);
                        int nhi2 = hi2 && (l2 == r2);
                        res += dfs(i + 1, nhi1, nhi2, (l1 == 0 && s1), (l2 == 0 && s2));
                    } else {
                        if (l1 + l2 != 9) {
                            continue;
                        }
                        int nhi1 = hi1 && (l1 == r1);
                        int nhi2 = hi2 && (l2 == r2);
                        res += dfs(i + 1, nhi1, nhi2, (l1 == 0 && s1), (l2 == 0 && s2));
                    }
                } else {
                    if (l1 + l2 != 9) {
                        continue;
                    }
                    int nhi1 = hi1 && (l1 == r1);
                    int nhi2 = hi2 && (l2 == r2);
                    res += dfs(i + 1, nhi1, nhi2, (l1 == 0 && s1), (l2 == 0 && s2));
                }
            }
        }

        return memo = res;
    };

    ll ans = dfs(0, 1, 1, 1, 1);
    ans /= 2;
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
