#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace utils {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
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
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }

    struct range : ranges::view_base {
        struct Iterator {
            using iterator_category = random_access_iterator_tag;
            using value_type = long long;
            using difference_type = ptrdiff_t;
            ll val, d;
            Iterator() = default;
            Iterator(ll val, ll d) : val(val), d(d) {};
            value_type operator*() const { return val; }
            Iterator &operator++() { return val += d, *this; }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            Iterator &operator--() { return val -= d, *this; }
            Iterator operator--(int) {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }
            difference_type operator-(const Iterator &other) const { return (val - other.val) / d; }
            bool operator==(const Iterator &other) const { return val == other.val; }
        };
        Iterator Begin, End;
        explicit range(ll n) : Begin(0, 1), End(max(n, ll{0}), 1) {};
        range(ll a, ll b, ll d = ll(1)) : Begin(a, d), End(b, d) {
            ll cnt = b == a or (b - a > 0) != (d > 0) ? 0 : (b - a) / d + bool((b - a) % d);
            End.val = a + max(cnt, ll(0)) * d;
        };
        [[nodiscard]] Iterator begin() const { return Begin; }
        [[nodiscard]] Iterator end() const { return End; };
        [[nodiscard]] ptrdiff_t size() const { return End - Begin; }
    };
} // namespace utils

using namespace utils;

#define int ll

int Multitest = 0;

void init() {}

void solve() {
    int n, d;
    rd(n, d);

    vector<vector<int>> g(n + 1);
    for (int _: range(n - 1)) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    set<int> stA, stB;
    int m;
    rd(m);
    for (int _: range(m)) {
        int t;
        rd(t);
        stA.insert(t);
    }

    rd(m);
    for (int _: range(m)) {
        int t;
        rd(t);
        stB.insert(t);
    }

    vector<int> dis(n + 1);
    auto dfs1 = [&](this auto &&dfs, int u, int fa) -> void {
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            dis[v] = dis[u] + 1;
            dfs(v, u);
        }
    };
    dfs1(1, 0);

    struct Info {
        int ca, totA, cb, totB, dA, dB;

        Info() : ca(-1), totA(0), cb(-1), totB(0), dA(-inf), dB(-inf) {}
    };

    vector<Info> dp(n + 1);
    auto dfs2 = [&](this auto &&dfs, int u, int fa) -> void {
        auto &cur = dp[u];
        int mxdA = -inf, mxdB = -inf;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs(v, u);
            auto [ca, totA, cb, totB, dA, dB] = dp[v];
            if (ca != -1) {
                if (cur.ca == -1) {
                    cur.ca = ca;
                } else {
                    cur.ca += ca;
                }
                cur.totA += totA + 1;
            }
            if (cb != -1) {
                if (cur.cb == -1) {
                    cur.cb = cb;
                } else {
                    cur.cb += cb;
                }
                cur.totB += totB + 1;
            }
            mxdA = max(mxdA, dA);
            mxdB = max(mxdB, dB);
        }

        if (stA.contains(u)) {
            if (cur.ca == -1) {
                cur.ca = 1;
            } else {
                cur.ca++;
            }
        }
        if (stB.contains(u)) {
            if (cur.cb == -1) {
                cur.cb = 1;
            } else {
                cur.cb++;
            }
        }

        int curD = dis[u];
        if (mxdA - curD >= d) {
            if (cur.cb == -1) {
                cur.cb = 1;
            }
            mxdA = -1;
        }
        if (mxdB - curD >= d) {
            if (cur.ca == -1) {
                cur.ca = 1;
            }
            mxdB = -1;
        }

        if (cur.ca != -1 && mxdA != -1) {
            mxdA = max(mxdA, curD);
        }
        if (cur.cb != -1 && mxdB != -1) {
            mxdB = max(mxdB, curD);
        }
        cur.dA = mxdA;
        cur.dB = mxdB;
    };
    dfs2(1, 0);
    int ans = 0;
    if (dp[1].ca != -1) {
        ans += dp[1].totA * 2;
    }
    if (dp[1].cb != -1) {
        ans += dp[1].totB * 2;
    }

    prt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
