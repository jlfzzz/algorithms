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
            ll sz = b == a or (b - a > 0) != (d > 0) ? 0 : (b - a) / d + bool((b - a) % d);
            End.val = a + max(sz, ll(0)) * d;
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
    int n;
    rd(n);

    vector<int> a(n + 1);
    rd_vec(a, 1);

    vector<int> pref(n + 1), pref2(n + 1);
    for (int i: range(1, n + 1)) {
        pref[i] = pref[i - 1] + a[i];
        pref2[i] = pref2[i - 1] + a[i] * i;
    }

    int sum = 0;
    for (int i: range(n, 0, -1)) {
        sum += a[i] * (n - i + 1);
    }

    vector<int> groups(n + 1), sz(n + 1);
    int pre = 0;
    for (int i: range(1, n + 1)) {
        groups[i] = sum - pre;
        pre += a[i] * (n - i + 1);

        sz[i] = n - i + 1;
    }

    vector<int> groupSum(n + 1), szSum(n + 1);
    for (int i: range(1, n + 1)) {
        groupSum[i] = groupSum[i - 1] + groups[i];
        szSum[i] = szSum[i - 1] + sz[i];
    }

    auto calc1 = [&](int i, int k) -> int {
        if (k <= 0)
            return 0;
        int r = min(n, i + k - 1);
        k = r - i + 1;
        int sumA = pref[r] - pref[i - 1];
        int sumAi = pref2[r] - pref2[i - 1];
        return (i + k) * sumA - sumAi;
    };

    auto calc2 = [&](int i, int k) -> int {
        if (k <= 0)
            return 0;
        int m = sz[i];
        if (k >= m)
            return groups[i];
        return groups[i] - calc1(i, m - k);
    };

    int q;
    rd(q);

    while (q--) {
        int l, r;
        rd(l, r);

        int L = ranges::lower_bound(szSum, l) - szSum.begin();
        int R = ranges::upper_bound(szSum, r) - szSum.begin();

        int ans = 0;
        if (L < R)
            ans = groupSum[R - 1] - groupSum[L];

        int takeLeft = szSum[L] - l + 1;
        int takeRight = r - szSum[R - 1];

        ans += calc2(L, takeLeft);
        ans += calc1(R, takeRight);

        if (L == R)
            ans -= groups[L];

        prt(ans);
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
