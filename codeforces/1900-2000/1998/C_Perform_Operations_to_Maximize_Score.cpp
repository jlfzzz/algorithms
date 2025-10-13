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
    int n, k;
    rd(n, k);

    vector<int> a(n), b(n);
    rd_vec(a);
    rd_vec(b);

    struct Info {
        int a, b, id;
    };

    vector<Info> arr(n);
    For(i, n) { arr[i] = {a[i], b[i], i}; }

    ranges::sort(arr, [](Info &a, Info &b) {
        if (a.a == b.a) {
            return a.b < b.b;
        }
        return a.a < b.a;
    });

    int pos = -1;
    for (int i: range(n - 1, -1, -1)) {
        if (arr[i].b == 1) {
            pos = i;
            break;
        }
    }

    int ans = 0;
    if (pos != -1) {
        vector<int> temp;
        For(i, n) {
            if (i != arr[pos].id) {
                temp.pb(a[i]);
            }
        }

        ranges::sort(temp);
        ans = k + temp[n / 2 - 1] + arr[pos].a;
        // if (n == 5 && k == 4 && a[0] == 7) {
        //     debug("arr[pos].a", arr[pos].a);
        //     debug("ans", ans);
        // }
    }

    int mx = arr[n - 1].a;

    // if (n == 5 && k == 4 && a[0] == 7) {
    //     debug("mx", mx);
    //     for (auto [a, b, c]: arr) {
    //         debug("a", a, "b", b, "c", c);
    //     }
    // }

    int zero = -1;
    for (int i: range(n - 1, -1, -1)) {
        if (arr[i].a != mx) {
            break;
        }

        if (arr[i].b == 0) {
            zero = i;
            break;
        }
    }

    vector<pii> arr2;
    if (zero == -1) {
        for (int i: range(n - 1)) {
            arr2.eb(arr[i].a, arr[i].b);
        }
    } else {
        for (int i: range(n)) {
            if (i == zero) {
                continue;
            }
            arr2.eb(arr[i].a, arr[i].b);
        }
    }

    int ans2 = 0;
    int lo = 1;
    int hi = 2e9 + k;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        auto check = [&](int med) {
            int use = 0;
            int less = 0;
            int lim = n / 2;

            priority_queue<int> pq;
            for (int i: range(n - 1)) {
                auto [a, b] = arr2[i];
                if (b == 0) {
                    if (a < med) {
                        less++;
                    }
                } else {
                    if (a < med) {
                        pq.push(a);
                        less++;
                    }
                }
                if (less == lim) {
                    if (pq.empty()) {
                        return false;
                    }
                    int x = pq.top();
                    pq.pop();
                    less--;
                    use += med - x;
                }
            }

            return use <= k;
        };

        if (check(mid)) {
            ans2 = mid;
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    ans = max(ans, ans2 + mx);
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
