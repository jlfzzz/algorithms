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

struct Node {
    int sum1, sum2, len, lazy;
};

class Seg {
public:
    vector<Node> tree;
    Seg(int n) : tree(4 * n + 5) {}

    void apply(Node &a, int lazy) {
        a.sum1 = a.sum1 + 2 * lazy * a.sum2 + lazy * lazy * a.len;
        a.sum2 = a.sum2 + a.len * lazy;
        a.lazy += lazy;
    }

    void pushdown(int o, int l, int r) {
        int lazy = tree[o].lazy;
        if (lazy != 0) {
            if (l != r) {
                apply(tree[o * 2], lazy);
                apply(tree[o * 2 + 1], lazy);
            }
            tree[o].lazy = 0;
        }
    }

    Node pushup(Node &a, Node &b) {
        Node res;
        res.sum1 = a.sum1 + b.sum1;
        res.sum2 = a.sum2 + b.sum2;
        res.len = a.len + b.len;
        res.lazy = 0;
        return res;
    }

    void rangeAdd(int o, int l, int r, int ql, int qr, int delta) {
        if (r < ql || l > qr) {
            return;
        }

        if (l >= ql && r <= qr) {
            apply(tree[o], delta);
            return;
        }

        int m = (l + r) / 2;
        pushdown(o, l, r);
        rangeAdd(o * 2, l, m, ql, qr, delta);
        rangeAdd(o * 2 + 1, m + 1, r, ql, qr, delta);
        tree[o] = pushup(tree[o * 2], tree[o * 2 + 1]);
    }

    int rangeCount(int o, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[o].len;
        }
        int m = (l + r) / 2;
        return rangeCount(o * 2, l, m, ql, qr) + rangeCount(o * 2 + 1, m + 1, r, ql, qr);
    }

    void set(int o, int l, int r, int pos, bool present, int val) {
        if (l == r) {
            tree[o].len = present ? 1 : 0;
            tree[o].sum2 = present ? val : 0;
            tree[o].sum1 = present ? val * val : 0;
            tree[o].lazy = 0;
            return;
        }
        pushdown(o, l, r);
        int m = (l + r) / 2;
        if (pos <= m) {
            set(o * 2, l, m, pos, present, val);
        } else {
            set(o * 2 + 1, m + 1, r, pos, present, val);
        }
        tree[o] = pushup(tree[o * 2], tree[o * 2 + 1]);
    }
};

int Multitest = 0;

void init() {}

constexpr int N = 2e5 + 5;

void solve() {
    int q, d;
    rd(q, d);

    Seg seg(N);
    set<int> st;

    while (q--) {
        int a;
        rd(a);

        if (st.contains(a)) {
            int L = a + 1;
            int R = min(a + d, N);
            if (L <= R) {
                seg.rangeAdd(1, 1, N, L, R, -1);
            }
            seg.set(1, 1, N, a, false, 0);
            st.erase(a);
        } else {
            int l = max((int) 1, a - d);
            int r = a - 1;
            int val = 0;
            if (l <= r) {
                val = seg.rangeCount(1, 1, N, l, r);
            }
            seg.set(1, 1, N, a, true, val);
            int L = a + 1;
            int R = min(a + d, N);
            if (L <= R) {
                seg.rangeAdd(1, 1, N, L, R, 1);
            }
            st.insert(a);
        }

        prt((seg.tree[1].sum1 - seg.tree[1].sum2) / 2);
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
