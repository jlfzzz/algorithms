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
    int n, a, b, c;
    rd(n, a, b, c);

    int start = 4;
    vector<pii> ans;
    if (a + b == c) {
        int pre = 1;
        for (int i: range(a - 1)) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        ans.eb(pre, 2);
        pre = 2;
        for (int i: range(b - 1)) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        ans.eb(pre, 3);
        pre = 3;
        while (start <= n) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
    } else if (b + c == a) {
        int pre = 1;
        for (int i: range(c - 1)) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        ans.eb(pre, 3);
        pre = 3;
        for (int i: range(b - 1)) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        ans.eb(pre, 2);
        pre = 2;
        while (start <= n) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
    } else if (a + c == b) {
        int pre = 1;
        for (int i: range(a - 1)) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        ans.eb(pre, 2);
        pre = 1;
        for (int i: range(c - 1)) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        ans.eb(pre, 3);
        pre = 3;
        while (start <= n) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
    } else {
        if ((a - c + b) % 2) {
            prt("NO");
            return;
        }

        if (a + b < c || a + c < b || b + c < a) {
            prt("NO");
            return;
        }

        int x = (a - c + b) / 2;
        if (x < 0 || x > b) {
            prt("NO");
            return;
        }
        map<int, int> parent;

        int pre = 1;
        for (int i: range(a - 1)) {
            parent[start] = pre;
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        parent[2] = pre;
        ans.eb(pre, 2);

        int t = 2;
        for (int i: range(x)) {
            t = parent[t];
        }

        pre = t;
        for (int i: range(b - x - 1)) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
        ans.eb(pre, 3);
        pre = 3;
        while (start <= n) {
            ans.eb(pre, start);
            pre = start;
            start++;
        }
    }

    if (ans.size() != n - 1) {
        prt("NO");
        return;
    }

    for (auto [x, y]: ans) {
        if (x > n || y > n || x < 1 || y < 1) {
            prt("NO");
            return;
        }
    }

    prt("YES");
    for (auto [x, y]: ans) {
        prt(x, y);
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
