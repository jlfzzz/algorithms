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

    vvi grid(n + 1, vi(n + 1));
    F(i, 1, n) { rv(grid[i], 1); }

    int zx = -1, zy = -1;
    F(i, 1, n) {
        F(j, 1, n) {
            if (grid[i][j] == 0) {
                zx = i;
                zy = j;
            }
        }
    }

    auto calc = [&](int prime) -> pair<ll, vvl> {
        auto temp = grid;
        F(i, 1, n) {
            F(j, 1, n) {
                ll t = temp[i][j];
                if (t == 0) {
                    temp[i][j] = inf;
                    continue;
                }
                int cnt = 0;
                while (t % prime == 0) {
                    cnt++;
                    t /= prime;
                }
                temp[i][j] = cnt;
            }
        }

        vvl dp(n + 1, vl(n + 1, INF));
        vvl prev(n + 1, vl(n + 1, -1));

        dp[1][1] = temp[1][1];

        F(i, 2, n) {
            dp[i][1] = dp[i - 1][1] + temp[i][1];
            prev[i][1] = 1;
        }
        F(j, 2, n) {
            dp[1][j] = dp[1][j - 1] + temp[1][j];
            prev[1][j] = 0;
        }
        F(i, 2, n) {
            F(j, 2, n) {
                if (dp[i - 1][j] < dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j] + temp[i][j];
                    prev[i][j] = 1;
                } else {
                    dp[i][j] = dp[i][j - 1] + temp[i][j];
                    prev[i][j] = 0;
                }
            }
        }

        return {dp[n][n], prev};
    };

    auto [c2, prev2] = calc(2);
    auto [c5, prev5] = calc(5);

    ll mn = min(c2, c5);
    string ans;
    ll best = 0;

    if (zx != -1 && mn > 1) {
        best = 1;
        int x = 1, y = 1;
        while (x < zx) {
            ans += 'D';
            x++;
        }
        while (y < zy) {
            ans += 'R';
            y++;
        }
        while (x < n) {
            ans += 'D';
            x++;
        }
        while (y < n) {
            ans += 'R';
            y++;
        }
    } else {
        best = mn;
        vvl &prev = (c2 <= c5) ? prev2 : prev5;

        int i = n, j = n;
        while (i != 1 || j != 1) {
            int dir = prev[i][j];
            if (dir == 1) {
                ans += 'D';
                i--;
            } else {
                ans += 'R';
                j--;
            }
        }
        ranges::reverse(ans);
    }

    prt(best);
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
