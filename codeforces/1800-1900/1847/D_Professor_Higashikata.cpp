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
    int n, m, q;
    rd(n, m, q);
    string s;
    cin >> s;
    vector<pair<int, int>> seg(m);
    for (int i: range(m)) {
        int l, r;
        rd(l, r);
        seg[i] = {l, r};
    }

    vector<int> nextPos(n + 2);
    for (int i = 1; i <= n + 1; i++) {
        nextPos[i] = i;
    }
    auto findNext = [&](auto &&self, int x) -> int {
        if (x > n + 1) {
            return n + 1;
        }
        if (nextPos[x] == x) {
            return x;
        } else {
            nextPos[x] = self(self, nextPos[x]);
            return nextPos[x];
        }
    };

    vector<int> order;
    for (int i: range(m)) {
        int l = seg[i].first;
        int r = seg[i].second;
        int p = findNext(findNext, l);
        while (p <= r) {
            order.push_back(p);
            nextPos[p] = findNext(findNext, p + 1);
            p = findNext(findNext, p);
        }
    }

    int covered = (int) order.size();
    vector<int> pos(n + 1, -1);
    for (int i: range(covered)) {
        pos[order[i]] = i + 1;
    }

    struct Fenwick {
        int size;
        vector<int> bit;
        explicit Fenwick(int n) : size(n), bit(n + 1, 0) {}
        void add(int idx, int delta) {
            for (int i = idx; i <= size; i += i & -i) {
                bit[i] += delta;
            }
        }
        int sum(int idx) const {
            int ans = 0;
            for (int i = idx; i > 0; i -= i & -i) {
                ans += bit[i];
            }
            return ans;
        }
    };

    Fenwick fw((int) covered);
    vector<int> a(n + 1, 0);
    for (int i: range(1, n + 1)) {
        a[i] = (s[i - 1] == '1') ? 1 : 0;
    }

    for (int i: range(covered)) {
        int idx = order[i];
        if (a[idx] == 1) {
            fw.add(i + 1, 1);
        }
    }

    int totalOnes = 0;
    for (int i: range(1, n + 1)) {
        if (a[i] == 1) {
            totalOnes += 1;
        }
    }

    auto get = [&](int ones) -> int {
        int L = min<int>(ones, covered);
        if (L <= 0) {
            return 0;
        } else {
            int onesInPrefix = fw.sum(L);
            return L - onesInPrefix;
        }
    };

    for (int _: range(q)) {
        int x;
        rd(x);
        if (a[x] == 1) {
            a[x] = 0;
            totalOnes -= 1;
            if (pos[x] != -1) {
                fw.add(pos[x], -1);
            }
        } else {
            a[x] = 1;
            totalOnes += 1;
            if (pos[x] != -1) {
                fw.add(pos[x], 1);
            }
        }
        int ans = get(totalOnes);
        cout << ans << '\n';
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
