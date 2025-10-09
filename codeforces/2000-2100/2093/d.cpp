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
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
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

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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

    int q;
    rd(q);

    while (q--) {
        string s;
        rd(s);

        if (s == "->") {
            int x, y;
            rd(x, y);

            auto dfs = [](this auto &&dfs, int power, int x, int y) -> int {
                if (power == 1) {
                    if (x == 1 && y == 1) {
                        return 1;
                    } else if (x == 1 && y == 2) {
                        return 4;
                    } else if (x == 2 && y == 2) {
                        return 2;
                    } else {
                        return 3;
                    }
                }

                int half = 1ll << (power - 1);
                int total = 1ll << (2 * power - 2);

                if (x <= half && y <= half) {
                    return dfs(power - 1, x, y);
                } else if (x > half && y > half) {
                    return dfs(power - 1, x - half, y - half) + total;
                } else if (x > half && y <= half) {
                    return dfs(power - 1, x - half, y) + 2 * total;
                } else {
                    return dfs(power - 1, x, y - half) + 3 * total;
                }
            };

            prt(dfs(n, x, y));
        } else {
            int d;
            rd(d);

            auto dfs = [](this auto &&dfs, int power, int d) -> pii {
                if (power == 1) {
                    if (d == 1) {
                        return {1, 1};
                    } else if (d == 2) {
                        return {2, 2};
                    } else if (d == 3) {
                        return {2, 1};
                    } else {
                        return {1, 2};
                    }
                }

                int total = 1ll << (2 * power - 2);
                int half = 1ll << (power - 1);

                if (d <= total) {
                    return dfs(power - 1, d);
                } else if (d <= 2 * total) {
                    auto [x, y] = dfs(power - 1, d - total);
                    return {x + half, y + half};
                } else if (d <= 3 * total) {
                    auto [x, y] = dfs(power - 1, d - 2 * total);
                    return {x + half, y};
                } else {
                    auto [x, y] = dfs(power - 1, d - 3 * total);
                    return {x, y + half};
                }
            };

            auto [a, b] = dfs(n, d);
            prt(a, b);
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
