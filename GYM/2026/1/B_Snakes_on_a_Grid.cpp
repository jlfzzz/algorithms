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
    int n, m;
    rd(n, m);

    vvi grid(n + 1, vi(m + 1));
    F(i, 1, n) { rv(grid[i], 1); }

    vvi d1(n + 1, vi(m + 1, 0));
    vvi d2(n + 1, vi(m + 1, 0));
    vvi d3(n + 1, vi(m + 1, 0));

    F(i, 1, n) {
        F(j, 1, m) {
            int c = grid[i][j];

            if (j >= 3) {
                if (grid[i][j - 1] == c && grid[i][j - 2] == c) {
                    d1[i][j] = 1;
                }
            }

            if (i >= 3) {
                if (grid[i - 1][j] == c && grid[i - 2][j] == c) {
                    d2[i][j] = 1;
                }
            }

            if (i >= 2 && j >= 2) {
                if (grid[i - 1][j] == c && grid[i][j - 1] == c && grid[i - 1][j - 1] == c) {
                    d3[i][j] = 1;
                }
            }
        }
    }

    F(i, 1, n) {
        F(j, 1, m) {
            d1[i][j] += d1[i - 1][j] + d1[i][j - 1] - d1[i - 1][j - 1];
            d2[i][j] += d2[i - 1][j] + d2[i][j - 1] - d2[i - 1][j - 1];
            d3[i][j] += d3[i - 1][j] + d3[i][j - 1] - d3[i - 1][j - 1];
        }
    }

    auto query = [&](vvi &s, int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2)
            return 0;
        return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
    };

    int q;
    rd(q);
    while (q--) {
        int x1, y1, x2, y2;
        rd(x1, y1, x2, y2);
        x1++;
        y1++;
        x2++;
        y2++;

        int f = false;

        if (query(d1, x1, y1 + 2, x2, y2) > 0)
            f = true;
        else if (query(d2, x1 + 2, y1, x2, y2) > 0)
            f = true;
        else if (query(d3, x1 + 1, y1 + 1, x2, y2) > 0)
            f = true;

        if (f)
            prt("NO");
        else
            prt("YES");
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
