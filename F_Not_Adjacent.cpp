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

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vector<int> arr1(n / 2), arr2(n - n / 2);
    rd_vec(arr1);
    rd_vec(arr2);

    auto encode = [&](int x, bool last) -> int { return x << 30 | last; };

    auto calc1 = [&](vector<int> &a) -> vector<pair<long long, long long>> {
        int sz = a.size();
        vector<long long> keys;
        // estimate independent sets ~ F_{sz+2}
        size_t f0 = 1, f1 = 1; // F2=1
        for (int i = 0; i < sz; ++i) {
            size_t fn = f0 + f1;
            f0 = f1;
            f1 = fn;
        }
        keys.reserve(f1 + 16);
        auto dfs = [&](auto &&dfs, int i, int sum, bool pre) -> void {
            if (i == sz) {
                keys.push_back(encode(sum, pre));
                return;
            }

            if (pre) {
                dfs(dfs, i + 1, sum, false);
                return;
            }

            dfs(dfs, i + 1, sum, false);
            dfs(dfs, i + 1, (sum + a[i]) % m, true);
        };
        dfs(dfs, 0, 0, false);

        sort(keys.begin(), keys.end());
        vector<pair<long long, long long>> res;
        res.reserve(keys.size());
        for (size_t i = 0; i < keys.size();) {
            size_t j = i + 1;
            while (j < keys.size() && keys[j] == keys[i])
                j++;
            res.emplace_back(keys[i], (long long) (j - i));
            i = j;
        }
        return res;
    };

    auto calc2 = [&](vector<int> &a) -> vector<pair<long long, long long>> {
        int sz = a.size();
        vector<long long> keys;
        // estimate independent sets ~ F_{sz+2}
        size_t f0 = 1, f1 = 1; // F2=1
        for (int i = 0; i < sz; ++i) {
            size_t fn = f0 + f1;
            f0 = f1;
            f1 = fn;
        }
        keys.reserve(f1 + 16);
        auto dfs = [&](auto &&dfs, int i, int sum, bool pre, bool first) -> void {
            if (i == sz) {
                keys.push_back(encode(sum, first));
                return;
            }

            if (pre) {
                dfs(dfs, i + 1, sum, false, first);
                return;
            }

            bool new_first = (i == 0) ? true : first;
            dfs(dfs, i + 1, (sum + a[i]) % m, true, new_first);
            dfs(dfs, i + 1, sum, false, first);
        };
        dfs(dfs, 0, 0, false, false);

        sort(keys.begin(), keys.end());
        vector<pair<long long, long long>> res;
        res.reserve(keys.size());
        for (size_t i = 0; i < keys.size();) {
            size_t j = i + 1;
            while (j < keys.size() && keys[j] == keys[i])
                j++;
            res.emplace_back(keys[i], (long long) (j - i));
            i = j;
        }
        return res;
    };

    for (auto &x: arr1)
        x %= m;
    for (auto &x: arr2)
        x %= m;
    auto cntL = calc1(arr1);
    auto cntR = calc2(arr2);

    auto getCnt = [&](const vector<pair<long long, long long>> &v, long long key) -> long long {
        auto it = lower_bound(v.begin(), v.end(), make_pair(key, 0LL),
                              [](const auto &a, const auto &b) { return a.first < b.first; });
        if (it != v.end() && it->first == key)
            return it->second;
        return 0LL;
    };

    int ans = 0;

    for (auto &p: cntL) {
        long long key = p.first;
        long long cnt1 = p.second;
        long long val1 = key >> 30;
        long long last = key & 1;

        long long val2 = (m - val1) % m;
        if (last) {
            ans += cnt1 * getCnt(cntR, (val2 << 30));
        } else {
            ans += cnt1 * (getCnt(cntR, (val2 << 30)) + getCnt(cntR, (val2 << 30 | 1)));
        }
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
