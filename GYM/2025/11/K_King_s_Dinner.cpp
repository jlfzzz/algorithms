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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);

    vector<string> ans(n, string(n, '.'));
    vector<vector<string>> d(7);
    d[1] = {"."};
    d[2] = {"#.", "#."};
    d[3] = {"#.#", "#.#", "..."};
    d[4] = {"#.##", "#...", "...#", "##.#"};
    d[5] = {"##.##", ".....", "##.##", ".....", "##.##"};
    d[6] = {"##.#.#", "...#.#", "##....", "....##", "#.#...", "#.#.##"};

    int v = (n - 1) % 6 + 1;
    for (int i = n - v; i < n; i++) {
        for (int j = n - v; j < n; j++) {
            ans[i][j] = d[v][i - (n - v)][j - (n - v)];
        }
    }

    if (n & 1) {
        for (int i = 0; i < n - v; i += 3) {
            for (int j = 0; j < n; j += 2) {
                ans[i][j] = '#';
                ans[i + 1][j] = '#';
            }
        }
    } else {
        for (int i = 0; i < n - v; i += 2) {
            ans[i][0] = '#';
            ans[i][1] = '#';
        }
        for (int i = 0; i < n - v; i += 3) {
            for (int j = 3; j < n; j += 2) {
                ans[i][j] = '#';
                ans[i + 1][j] = '#';
            }
        }
    }

    if (v & 1) {
        for (int i = n - v; i < n; i += 2) {
            for (int j = 0; j < n - v; j += 3) {
                ans[i][j] = '#';
                ans[i][j + 1] = '#';
            }
        }
    } else {
        for (int j = 0; j < n - v; j += 2) {
            ans[n - v][j] = '#';
            ans[n - v + 1][j] = '#';
        }
        for (int i = n - v + 3; i < n; i += 2) {
            for (int j = 0; j < n - v; j += 3) {
                ans[i][j] = '#';
                ans[i][j + 1] = '#';
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
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
