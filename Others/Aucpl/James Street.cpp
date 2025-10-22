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

// https://aucpl.com/problem/jamesstreet

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
    int n;
    rd(n);

    vector<vector<pii>> g(n + 1);
    for (int _: range(n - 1)) {
        int u, v, t;
        rd(u, v, t);
        g[u].eb(v, t);
        g[v].eb(u, t);
    }

    vector<int> ans(n + 1);
    vector<int> msk(n + 1);
    auto build = [&](auto &&build, int u, int fa) -> void {
        for (auto [v, x]: g[u]) {
            if (v == fa) {
                continue;
            }
            msk[v] = msk[u] ^ (1LL << (x - 1));
            build(build, v, u);
        }
    };
    build(build, 1, 0);

    auto dfs = [&](auto &&dfs, int u, int fa) -> unordered_map<int, int> {
        unordered_map<int, int> big;
        for (auto [v, x]: g[u]) {
            if (v == fa) {
                continue;
            }

            auto sub = dfs(dfs, v, u);
            ans[u] += ans[v];

            if (sub.size() > big.size()) {
                swap(sub, big);
            }

            for (auto &kv: sub) {
                int s = kv.first;
                int c = kv.second;
                int add = 0;
                auto it0 = big.find(s);
                if (it0 != big.end()) {
                    add += it0->second;
                }
                for (int i: range(20)) {
                    int m = s ^ (1LL << i);
                    auto it = big.find(m);
                    if (it != big.end()) {
                        add += it->second;
                    }
                }
                ans[u] += c * add;
            }

            for (auto &kv: sub) {
                big[kv.first] += kv.second;
            }
        }

        int addU = 0;
        auto it0 = big.find(msk[u]);
        if (it0 != big.end()) {
            addU += it0->second;
        }
        for (int i: range(20)) {
            int m = msk[u] ^ (1LL << i);
            auto it = big.find(m);
            if (it != big.end()) {
                addU += it->second;
            }
        }
        ans[u] += addU;
        big[msk[u]] += 1;
        return big;
    };

    dfs(dfs, 1, 0);
    prt_vec(ans, 1);
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
