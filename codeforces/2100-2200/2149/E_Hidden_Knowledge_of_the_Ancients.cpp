#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}
#include <bits/stdc++.h>
using namespace std;


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
    int x;
};

struct F {
    int lazy;
};

S op(S a, S b) { return {min(a.x, b.x)}; }
S e() { return {int(1e9 + 5)}; }

S mapping(F f, S x) {
    if (f.lazy == -1)
        return x;

    return {x.x};
}

F composition(F f, F g) {
    if (f.lazy == -1) {
        return g;
    }
    return f;
}

F id() { return {-1}; }



void solve() {
    int n, k, l, r;
    cin >> n >> k >> l >> r;

    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> nxt_pos(n, -1);
    map<int, int> last;
    for (int i = n - 1; i >= 0; --i) {
        int x = a[i];
        auto it = last.find(x);
        if (it != last.end())
            nxt_pos[i] = it->second;
        last[x] = i;
    }

    S init = e();
    vector<S> tree_arr(n + 1, init);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(tree_arr);
    seg.set(n, {-1});
    {
        map<int, int> temp;
        for (int i = 0; i < n; i++) {
            if (!temp.count(a[i])) {
                seg.set(i, {-1});
                temp[a[i]] = 1;
            }
        }
    }

    ll ans = 0;
    map<int, int> window;
    int left = 0;
    int right = -1;

    auto f = [&](S x) -> bool { return x.x != -1; };

    for (left = 0; left < n; left++) {
        while (right + 1 < n && window.size() < k) {
            right++;
            int v = a[right];
            window[v]++;
            if (nxt_pos[right] != -1) {
                seg.set(nxt_pos[right], {1});
            }
        }

        if (window.size() < k) {
            break;
        }

        int start = right + 1;
        int p = (start <= n - 1) ? seg.max_right(start, f) : n;
        int end_max = min(p - 1, left + r - 1);
        int end_min = max(right, left + l - 1);
        if (end_max >= end_min)
            ans += (end_max - end_min + 1);

        int y = a[left];
        auto it = window.find(y);
        if (--(it->second) == 0) {
            window.erase(it);
            if (nxt_pos[left] != -1) {
                seg.set(nxt_pos[left], {-1});
            }
        }
    }

    cout << ans << '\n';
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
