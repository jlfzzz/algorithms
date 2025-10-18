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
    int n, q;
    rd(n, q);

    string s;
    rd(s);

    vector<pii> pre(n + 1), suf(n + 2);
    map<ull, vector<int>> pre2, suf2;

    auto encode = [&](ll x, ll y) -> ull { return ((ull) (uint32_t) (x) << 32) | (ull) (uint32_t) (y); };
    auto decode = [&](ull mask) -> pii { return {(ll) (int32_t) (mask >> 32), (ll) (int32_t) (mask & 0xffffffffull)}; };

    pre2[encode(pre[0].first, pre[0].second)].pb(0);
    for (int i: range(n)) {
        pre[i + 1] = pre[i];
        if (s[i] == 'R') {
            pre[i + 1].first++;
        } else if (s[i] == 'L') {
            pre[i + 1].first--;
        } else if (s[i] == 'U') {
            pre[i + 1].second++;
        } else {
            pre[i + 1].second--;
        }

        pre2[encode(pre[i + 1].first, pre[i + 1].second)].pb(i + 1);
    }

    for (int i: range(n, 0, -1)) {
        suf[i] = suf[i + 1];
        if (s[i - 1] == 'R') {
            suf[i].first++;
        } else if (s[i - 1] == 'L') {
            suf[i].first--;
        } else if (s[i - 1] == 'U') {
            suf[i].second++;
        } else {
            suf[i].second--;
        }

        suf2[encode(suf[i].first, suf[i].second)].pb(i);
    }

    for (auto &[_, v]: suf2) {
        ranges::sort(v);
    }

    while (q--) {
        int x, y, l, r;
        rd(x, y, l, r);

        auto it1 = pre2.find(encode(x, y));
        if (it1 != pre2.end()) {
            int i = it1->second[0];
            if (i < l) {
                prt("YES");
                continue;
            }
            int j = it1->second.back();
            if (j > r) {
                prt("YES");
                continue;
            }
        }

        auto [tx, ty] = pre[l - 1];
        int dx = x - tx, dy = y - ty;
        auto [sufx, sufy] = suf[r + 1];
        int ttx = sufx + dx, tty = sufy + dy;
        auto it2 = suf2.find(encode(ttx, tty));
        if (it2 != suf2.end()) {
            auto it = ranges::lower_bound(it2->second, l);
            if (it != it2->second.end() && *it <= r) {
                prt("YES");
                continue;
            }
        }

        prt("NO");
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
