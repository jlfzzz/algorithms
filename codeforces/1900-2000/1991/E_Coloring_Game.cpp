#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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
    int n, m;
    rd(n, m);

    vector<vector<int>> g(n + 1);
    for (auto _: range(m)) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    bool bob = false;


    vector<int> colors(n + 1, -1);
    auto dfs = [&](this auto &&dfs, int u, int c, int fa) -> bool {
        if (bob) {
            return false;
        }
        colors[u] = c;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            if (colors[v] != -1) {
                if (colors[v] == c) {
                    bob = true;
                    return false;
                }
                continue;
            }

            if (!dfs(v, c ^ 1, u)) {
                bob = true;
                return false;
            }
        }

        return true;
    };

    dfs(1, 0, 0);


    if (bob) {
        cout << "Alice" << endl;

        for (int _: range(n)) {
            cout << 1 << ' ' << 2 << endl;
            int i, c;
            rd(i, c);
        }
    } else {
        cout << "Bob" << endl;

        vector<int> odd, even;

        for (int i: range(1, n + 1)) {
            if (colors[i]) {
                odd.pb(i);
            } else {
                even.pb(i);
            }
        }
        int p_even = 0, p_odd = 0;
        for (int _: range(n)) {
            int a, b;
            rd(a, b);

            auto has = [&](int c) -> bool { return a == c || b == c; };

            bool even_left = p_even < even.size();
            bool odd_left = p_odd < odd.size();

            if (has(1) && even_left && (!has(2) || !odd_left)) {
                cout << even[p_even++] << ' ' << 1 << endl;
            } else if (has(2) && odd_left) {
                cout << odd[p_odd++] << ' ' << 2 << endl;
            } else if (has(1) && even_left) {
                cout << even[p_even++] << ' ' << 1 << endl;
            } else if (even_left) {
                int c = has(3) ? 3 : 1;
                cout << even[p_even++] << ' ' << c << endl;
            } else if (odd_left) {
                int c = has(2) ? 2 : 3;
                cout << odd[p_odd++] << ' ' << c << endl;
            }
        }
    }
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
