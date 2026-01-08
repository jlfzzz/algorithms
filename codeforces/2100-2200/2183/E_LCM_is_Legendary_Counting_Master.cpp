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

int Multitest = 1;

constexpr int N = 3005;
vi divs[N];

void init() {
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
}

void solve() {
    int n, m;
    rd(n, m);

    vi a(n);
    rv(a);

    auto Add = [&](ll &x, ll y) {
        x += MOD + y;
        x %= MOD;
    };

    if (a[0] != 0 && a[0] != 1) {
        prt(0);
        return;
    }

    vl dp(m + 1, 0);
    dp[1] = 1;

    F(i, 1, n - 1) {
        vl ndp(m + 1, 0);

        F(j, 1, m) {
            if (dp[j] == 0)
                continue;

            for (int d: divs[j]) {
                int nxt = j + d;
                if (nxt > m)
                    continue;

                if (a[i] == 0 || a[i] == nxt) {
                    Add(ndp[nxt], dp[j]);
                }
            }
        }
        dp.swap(ndp);
    }

    ll ans = 0;
    F(j, 1, m) { Add(ans, dp[j]); }
    prt(ans);

    // auto lcm = [&](ll x, ll y) { return x * y / gcd(x, y); };

    // auto dfs = [&](this auto &&dfs, vl &path, ll pre, int d) -> void {
    //     if (d == 8) {
    //         db tot = 0;
    //         F(i, 0, 6) {
    //             ll l = lcm(path[i], path[i + 1]);
    //             tot += 1.0 / (db) l;
    //         }

    //         tot += 1.0 / (db) lcm(path.back(), path[0]);
    //         if (abs(tot - 1) <= 1e-9) {
    //             dbg(path);
    //         }
    //         return;
    //     }

    //     F(nxt, pre + 1, 21) {
    //         path.pb(nxt);
    //         dfs(path, nxt, d + 1);
    //         path.pob();
    //     }
    // };
    // vl t;
    // dfs(t, 0, 0);
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
