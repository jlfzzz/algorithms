#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define ld long double
#define db double
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
    void rd(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void rd(T &x, Args &...args) {
        cin >> x;
        rd(args...);
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

void solve() {
    int n;
    int R;
    rd(n, R);
    vector<pair<int, int>> points(n);
    for (int i: range(n)) {
        int x, y;
        rd(x, y);
        points[i] = {x, y};
    }

    const ld PI = acos(-1.0L);
    const ld TWO_PI = 2.0L * PI;
    const ld EPS = 1e-12;

    int ans = 1;
    vector<pair<ld, int>> evs;

    for (int i: range(n)) {
        evs.clear();
        evs.reserve(2 * (n - 1) + 8);
        int starts = 0;
        for (int j: range(n)) {
            if (i == j) {
                continue;
            }
            ld dx = points[j].first - points[i].first;
            ld dy = points[j].second - points[i].second;
            ld d2 = dx * dx + dy * dy;
            ld lim = 4.0L * (ld) R * (ld) R;
            if (d2 > lim + 1e-18L) {
                continue;
            }
            ld d = sqrtl(d2);
            ld base = atan2(dy, dx);
            ld ratio = d / (2.0L * R);
            if (ratio < -1.0) {
                ratio = -1.0;
            }
            if (ratio > 1.0) {
                ratio = 1.0;
            }
            ld delta = acos(ratio);
            ld L = base - delta;
            ld RR = base + delta;
            if (L < 0) {
                L += TWO_PI;
                if (L < 0) {
                    L += TWO_PI;
                }
            }
            if (L >= TWO_PI) {
                L -= TWO_PI;
                if (L >= TWO_PI) {
                    L -= TWO_PI;
                }
            }
            if (RR < 0) {
                RR += TWO_PI;
                if (RR < 0) {
                    RR += TWO_PI;
                }
            }
            if (RR >= TWO_PI) {
                RR -= TWO_PI;
                if (RR >= TWO_PI) {
                    RR -= TWO_PI;
                }
            }
            if (L <= RR) {
                evs.emplace_back(L, +1);
                starts++;
                evs.emplace_back(RR, -1);
            } else {
                evs.emplace_back(L, +1);
                starts++;
                evs.emplace_back(TWO_PI, -1);
                evs.emplace_back(0.0L, +1);
                starts++;
                evs.emplace_back(RR, -1);
            }
        }
        if (starts + 1 <= ans) {
            continue;
        }
        sort(evs.begin(), evs.end(), [](const auto &a, const auto &b) {
            if (fabs(a.first - b.first) > 1e-18) {
                return a.first < b.first;
            }
            return a.second > b.second;
        });
        int curr = 0;
        for (const auto &e: evs) {
            curr += e.second;
            if (ans < curr + 1) {
                ans = curr + 1;
            }
        }
        if (ans == n) {
            break;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--) {
        solve();
    }
    return 0;
}
