#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

struct SegmentTreeNode {
    ll mx, mn;
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    SegmentTreeNode merge(const SegmentTreeNode &left, const SegmentTreeNode &right) {
        return {max(left.mx, right.mx), min(left.mn, right.mn)};
    }

    void build(const vector<ll> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = {nums[l], nums[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node] = {val, val};
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return LLONG_MIN;
        if (ql <= l && r <= qr)
            return tree[node].mx;
        int mid = (l + r) / 2;
        return max(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
    }

    ll query2(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return LLONG_MAX;
        if (ql <= l && r <= qr)
            return tree[node].mn;
        int mid = (l + r) / 2;
        return min(query2(node * 2, l, mid, ql, qr), query2(node * 2 + 1, mid + 1, r, ql, qr));
    }

public:
    // 1-index
    explicit SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        tree.resize(4 * n + 5);
        build(nums, 1, 1, n);
    }

    explicit SegmentTree(int n) : n(n), tree(4 * n + 5) {}

    void update(int idx, ll val) { update(1, 1, n, idx, val); }

    ll rangeMax(int l, int r) { return query(1, 1, n, l, r); }

    ll rangeMin(int l, int r) { return query2(1, 1, n, l, r); }

    ll getValue(int idx) { return rangeMax(idx, idx); }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    SegmentTree segB(n + 1), segA(n + 1);
    for (int i = 1; i <= n; i++) {
        segB.update(i, b[i - 1]);
        segA.update(i, a[i - 1]);
    }

    vector<int> las(n + 2, -1);
    vector<bool> ok(n, 0);

    for (int i = 0; i < n; i++) {
        las[a[i]] = i;
        int p = las[b[i]];
        if (p == -1)
            continue;
        int mn = segB.rangeMin(p + 1, i + 1);
        int mx = segA.rangeMax(p + 1, i + 1);
        if (mn >= b[i] && mx <= b[i])
            ok[i] = 1;
    }

    fill(las.begin(), las.end(), -1);
    for (int i = n - 1; i >= 0; i--) {
        las[a[i]] = i;
        int p = las[b[i]];
        if (p == -1)
            continue;
        int mn = segB.rangeMin(i + 1, p + 1);
        int mx = segA.rangeMax(i + 1, p + 1);
        if (mn >= b[i] && mx <= b[i])
            ok[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (!ok[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
// #define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}
namespace atcoder::internal {

#if __cplusplus >= 202002L

    using std::bit_ceil;

#else

    unsigned int bit_ceil(unsigned int n) {
        unsigned int x = 1;
        while (x < (unsigned int) (n))
            x *= 2;
        return x;
    }

#endif

    int countr_zero(unsigned int n) {
#ifdef _MSC_VER
        unsigned long index;
        _BitScanForward(&index, n);
        return index;
#else
        return __builtin_ctz(n);
#endif
    }

    constexpr int countr_zero_constexpr(unsigned int n) {
        int x = 0;
        while (!(n & (1 << x)))
            x++;
        return x;
    }

} // namespace atcoder::internal

namespace atcoder {

#if __cplusplus >= 201703L

    template<class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
    struct lazy_segtree {
        static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
        static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");
        static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>, "mapping must work as S(F, S)");
        static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
                      "composition must work as F(F, F)");
        static_assert(std::is_convertible_v<decltype(id), std::function<F()>>, "id must work as F()");

#else

    template<class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
    struct lazy_segtree {

#endif

    public:
        lazy_segtree() : lazy_segtree(0) {}
        explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
        explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size())) {
            size = (int) internal::bit_ceil((unsigned int) (_n));
            log = internal::countr_zero((unsigned int) size);
            d = std::vector<S>(2 * size, e());
            lz = std::vector<F>(size, id());
            for (int i = 0; i < _n; i++)
                d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--) {
                update(i);
            }
        }

        void set(int p, S x) {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            d[p] = x;
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }

        S get(int p) {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            return d[p];
        }

        S prod(int l, int r) {
            assert(0 <= l && l <= r && r <= _n);
            if (l == r)
                return e();

            l += size;
            r += size;

            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l)
                    push(l >> i);
                if (((r >> i) << i) != r)
                    push((r - 1) >> i);
            }

            S sml = e(), smr = e();
            while (l < r) {
                if (l & 1)
                    sml = op(sml, d[l++]);
                if (r & 1)
                    smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }

            return op(sml, smr);
        }

        S all_prod() { return d[1]; }

        void apply(int p, F f) {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            d[p] = mapping(f, d[p]);
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }
        void apply(int l, int r, F f) {
            assert(0 <= l && l <= r && r <= _n);
            if (l == r)
                return;

            l += size;
            r += size;

            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l)
                    push(l >> i);
                if (((r >> i) << i) != r)
                    push((r - 1) >> i);
            }

            {
                int l2 = l, r2 = r;
                while (l < r) {
                    if (l & 1)
                        all_apply(l++, f);
                    if (r & 1)
                        all_apply(--r, f);
                    l >>= 1;
                    r >>= 1;
                }
                l = l2;
                r = r2;
            }

            for (int i = 1; i <= log; i++) {
                if (((l >> i) << i) != l)
                    update(l >> i);
                if (((r >> i) << i) != r)
                    update((r - 1) >> i);
            }
        }

        template<bool (*g)(S)>
        int max_right(int l) {
            return max_right(l, [](S x) { return g(x); });
        }
        template<class G>
        int max_right(int l, G g) {
            assert(0 <= l && l <= _n);
            assert(g(e()));
            if (l == _n)
                return _n;
            l += size;
            for (int i = log; i >= 1; i--)
                push(l >> i);
            S sm = e();
            do {
                while (l % 2 == 0)
                    l >>= 1;
                if (!g(op(sm, d[l]))) {
                    while (l < size) {
                        push(l);
                        l = (2 * l);
                        if (g(op(sm, d[l]))) {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return _n;
        }

        template<bool (*g)(S)>
        int min_left(int r) {
            return min_left(r, [](S x) { return g(x); });
        }
        template<class G>
        int min_left(int r, G g) {
            assert(0 <= r && r <= _n);
            assert(g(e()));
            if (r == 0)
                return 0;
            r += size;
            for (int i = log; i >= 1; i--)
                push((r - 1) >> i);
            S sm = e();
            do {
                r--;
                while (r > 1 && (r % 2))
                    r >>= 1;
                if (!g(op(d[r], sm))) {
                    while (r < size) {
                        push(r);
                        r = (2 * r + 1);
                        if (g(op(d[r], sm))) {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;
        std::vector<F> lz;

        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
        void all_apply(int k, F f) {
            d[k] = mapping(f, d[k]);
            if (k < size)
                lz[k] = composition(f, lz[k]);
        }
        void push(int k) {
            all_apply(2 * k, lz[k]);
            all_apply(2 * k + 1, lz[k]);
            lz[k] = id();
        }
    };

} // namespace atcoder

struct S {
    int mx, mn;
};

struct F {
    int lazy;
};

S op(S a, S b) { return {max(a.mx, b.mx), min(a.mn, b.mn)}; }

S e() { return {INT_MIN, INT_MAX}; }

S mapping(F f, S x) {
    if (f.lazy == -1)
        return x;

    return {1, 1};
}

F composition(F f, F g) {
    if (f.lazy == -1) {
        return g;
    }
    return f;
}

F id() { return {-1}; }

void solve() {
    int n;
    cin >> n;

    vector<S> a(n), b(n);
    For(i, n) {
        int x;
        cin >> x;
        a[i] = {x, x};
    }
    For(i, n) {
        int x;
        cin >> x;
        b[i] = {x, x};
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> segA(a), segB(b);

    vector<int> last(n + 1, -1), ok(n);

    for (int i = 0; i < n; i++) {
        int x = a[i].mx, y = b[i].mx;
        last[x] = i;

        if (last[y] == -1) {
            continue;
        }

        int j = last[y];

        int mx = segA.prod(j, i + 1).mx;
        int mn = segB.prod(j, i + 1).mn;

        if (mx > y || mx > mn) {
            continue;
        }

        ok[i] = 1;
    }

    ranges::fill(last, -1);

    for (int i = n - 1; i >= 0; i--) {
        int x = a[i].mx, y = b[i].mx;
        last[x] = i;

        if (last[y] == -1) {
            continue;
        }

        int j = last[y];

        int mx = segA.prod(i, j + 1).mx;
        int mn = segB.prod(i, j + 1).mn;

        if (mx > y || mx > mn) {
            continue;
        }

        ok[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (!ok[i]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
