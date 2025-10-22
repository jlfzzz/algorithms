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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    vector<int> a(n + 1);
    rd_vec(a, 1);

    vector<int> vis(n + 1);
    vector<int> instk(n + 1);
    auto dfs = [&](this auto &&dfs, int u) -> int {
        if (u < 1 || u > n) {
            return 2;
        }
        if (vis[u] != 0) {
            return vis[u];
        }
        if (instk[u]) {
            vis[u] = 1;
            return 1;
        }
        instk[u] = 1;
        int res = dfs(u + a[u]);
        instk[u] = 0;
        vis[u] = res;
        return res;
    };

    int cntEnd = 0;
    for (int i: range(1, n + 1)) {
        if (!vis[i]) {
            dfs(i);
        }
    }

    for (int i: range(1, n + 1)) {
        if (vis[i] == 2) {
            cntEnd++;
        }
    }

    int ans = 0;
    vector<int> inpath(n + 1);
    vector<int> idx(n + 1);
    int L = 0;
    {
        int t = 1;
        while (true) {
            if (t < 1 || t > n) {
                break;
            }
            if (inpath[t]) {
                break;
            }
            inpath[t] = 1;
            idx[t] = ++L;
            t += a[t];
        }
    }

    if (vis[1] == 2) {
        ans = (n - L) * (2 * n + 1);

        vector<int> memo(n + 1, -1);
        auto f = [&](this auto &&f, int u) -> int {
            if (u < 1 || u > n) {
                return 0;
            }
            if (idx[u] != 0) {
                return idx[u];
            }
            if (memo[u] != -1) {
                return memo[u];
            }
            int v = u + a[u];
            int r = f(v);
            memo[u] = r;
            return r;
        };

        int cnt = 0;
        vector<int> meet(L + 1);
        for (int u: range(1, n + 1)) {
            if (vis[u] == 2) {
                if (idx[u] == 0) {
                    int p = f(u);
                    if (p == 0) {
                        cnt++;
                    } else {
                        meet[p]++;
                    }
                }
            }
        }

        int add = L * cnt;
        for (int p: range(1, L + 1)) {
            add += meet[p] * (p - 1);
        }

        ans += L * (n + 1);
        ans += (L * (L - 1)) / 2;
        ans += add;
    } else {
        ans = L * (n + 1 + cntEnd);
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
