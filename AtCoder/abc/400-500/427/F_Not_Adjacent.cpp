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

    auto calc1 = [&](vector<int> &a) -> unordered_map<int, int> {
        int sz = a.size();
        unordered_map<int, int> res;
        res.reserve(1 << 18);
        auto dfs = [&](auto &&dfs, int i, int sum, bool pre) -> void {
            if (i == sz) {
                int key = encode(sum, pre);
                auto it = res.find(key);
                if (it == res.end())
                    res.emplace(key, 1);
                else
                    ++it->second;
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

        return res;
    };

    auto calc2 = [&](vector<int> &a) -> unordered_map<int, int> {
        int sz = a.size();
        unordered_map<int, int> res;
        res.reserve(1 << 18);
        auto dfs = [&](auto &&dfs, int i, int sum, bool pre, bool first) -> void {
            if (i == sz) {
                int key = encode(sum, first);
                auto it = res.find(key);
                if (it == res.end())
                    res.emplace(key, 1);
                else
                    ++it->second;
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

        return res;
    };

    for (auto &x: arr1)
        x %= m;
    for (auto &x: arr2)
        x %= m;
    auto cntL = calc1(arr1);
    auto cntR = calc2(arr2);

    int ans = 0;

    for (auto &[key, cnt1]: cntL) {
        int val1 = key >> 30;
        int last = key & 1;

        if (last) {
            int val2 = (m - val1) % m;
            auto it0 = cntR.find(val2 << 30);
            if (it0 != cntR.end())
                ans += cnt1 * it0->second;
        } else {
            int val2 = (m - val1) % m;
            auto it0 = cntR.find(val2 << 30);
            if (it0 != cntR.end())
                ans += cnt1 * it0->second;
            auto it1 = cntR.find(val2 << 30 | 1);
            if (it1 != cntR.end())
                ans += cnt1 * it1->second;
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
