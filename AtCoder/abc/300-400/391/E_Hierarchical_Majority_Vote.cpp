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

int pow3[30];

void init() {
    pow3[0] = 1;
    F(i, 1, 15) { pow3[i] = pow3[i - 1] * 3; }
}

void solve() {
    int n;
    rd(n);

    string s;
    rd(s);
    vi a(pow3[n] + 1);
    F(i, 1, pow3[n]) { a[i] = s[i - 1] - '0'; }

    int m = pow3[n];

    map<pii, int> old_vals;

    auto dfs1 = [&](auto &&dfs, int l, int r) {
        if (l == r) {
            return old_vals[{l, r}] = a[l];
        }
        int len = r - l + 1;
        int t = len / 3;
        int c = dfs(dfs, l, l + t - 1) + dfs(dfs, l + t, l + 2 * t - 1) + dfs(dfs, l + 2 * t, r);
        if (c >= 2) {
            return old_vals[{l, r}] = 1;
        }
        return old_vals[{l, r}] = 0;
    };

    dfs1(dfs1, 1, m);

    auto dfs2 = [&](auto &&dfs, int l, int r) -> int {
        if (l == r) {
            return 1;
        }

        int len = r - l + 1;
        int t = len / 3;

        int l1 = l, r1 = l + t - 1;
        int l2 = l + t, r2 = l + 2 * t - 1;
        int l3 = l + 2 * t, r3 = r;

        int curVal = old_vals[{l, r}];
        int target = curVal ^ 1;

        vi costs;

        auto get_cost = [&](int sl, int sr, int targetVal) {
            if (old_vals[{sl, sr}] == targetVal)
                return 0;
            return dfs(dfs, sl, sr);
        };

        costs.pb(get_cost(l1, r1, target));
        costs.pb(get_cost(l2, r2, target));
        costs.pb(get_cost(l3, r3, target));

        sort(all(costs));

        return costs[0] + costs[1];
    };

    prt(dfs2(dfs2, 1, m));
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
