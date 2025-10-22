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

// https://aucpl.com/contest/2025round8au

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

template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 左闭右闭
    T rangeSum(int l, int r) const { return this->pre(r) - this->pre(l - 1); }

    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    T getVal(int i) { return rangeSum(i, i); }

    void setVal(int i, T val) {
        T delta = val - getVal(i);
        update(i, delta);
    }
};

#define int ll

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);

    vector<pii> friends(n);
    vector<int> ts;
    for (int i: range(n)) {
        rd(friends[i].first, friends[i].second);
        ts.pb(friends[i].first);
        ts.pb(friends[i].second);
    }

    int m;
    rd(m);
    struct Act {
        int l, r, val;
    };
    vector<Act> act(m);
    for (int i: range(m)) {
        int l, r, val;
        rd(l, r, val);
        act[i] = {l, r, val};
        ts.pb(l);
        ts.pb(r);
    }

    ranges::sort(ts);
    ts.erase(unique(all(ts)), ts.end());

    // 1-index
    auto getIdx = [&](int val) -> int { return ranges::lower_bound(ts, val) - ts.begin() + 1; };

    int N = ts.size() + 5;
    vector<vector<int>> ev1(N);
    vector<vector<pii>> ev2(N);

    // debug("ts sz", N);

    for (auto &[s, t]: friends) {
        int i = getIdx(s);
        int j = getIdx(t);

        ev1[i].pb(j);
    }

    for (auto &[l, r, val]: act) {
        int i = getIdx(l);
        int j = getIdx(r);

        ev2[i].eb(j, val);
    }

    FenwickTree<ll> fwt(N + 5);
    vector<int> dp(N + 5);
    int pre = 0;
    dp[0] = 0;
    int sz = ts.size();
    for (int i: range(1, sz + 1)) {
        dp[i + 1] = max(dp[i + 1], dp[i]);

        // debug("i", i, "pre", pre, "ended", fwt.pre(i - 1), "dp[i]", dp[i]);

        for (auto r: ev1[i]) {
            pre++;
            fwt.update(r, 1);
        }

        for (auto &[end, val]: ev2[i]) {
            int cnt = pre - fwt.pre(end - 1);
            dp[end + 1] = max(dp[end + 1], dp[i] + cnt * val);
        }
    }

    int ans = ranges::max(dp);
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
