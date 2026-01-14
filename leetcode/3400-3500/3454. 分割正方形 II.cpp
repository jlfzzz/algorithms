#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
int INIT = [] { return 0; }();

using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define U(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

namespace atcoder {
    namespace internal {

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

    } // namespace internal

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
    ll sum;
    ll cnt;
    ll len;
};

struct F {
    int lazy;
};

S op(S a, S b) {
    S res;
    res.len = a.len + b.len;
    res.cnt = min(a.cnt, b.cnt);
    res.sum = 0;
    if (a.cnt == res.cnt)
        res.sum += a.sum;
    if (b.cnt == res.cnt)
        res.sum += b.sum;
    return res;
}

S e() { return {0, INF, 0}; }

S mapping(F f, S x) {
    if (x.cnt == INF)
        return x;
    return {x.sum, x.cnt + f.lazy, x.len};
}

F composition(F f, F g) { return {f.lazy + g.lazy}; }

F id() { return {0}; }

class Solution {
public:
    double separateSquares(vector<vector<int>> &squares) {
        vl temp;
        for (auto &v: squares) {
            ll x = v[0];
            temp.pb(x);
            temp.pb(x + v[2]);
        }

        ranges::sort(temp);
        temp.erase(unique(all(temp)), temp.end());
        int m = SZ(temp);

        auto Get = [&](ll x) { return ranges::lower_bound(temp, x) - temp.begin(); };

        vector<S> tree_arr(m + 5);
        U(i, 0, m - 2) {
            ll L = temp[i + 1] - temp[i];
            tree_arr[i] = {L, 0, L};
        }
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(tree_arr);

        // 0 insert, 1 delete
        struct Q {
            ll x, len, op;
        };
        map<ll, vector<Q>> pos;
        for (auto &v: squares) {
            ll x = v[0], y = v[1], len = v[2];
            pos[y].pb(x, len, 0);
            pos[y + len].pb(x, len, 1);
        }

        ll tot = 0;
        ll pre = pos.begin()->fi;
        for (auto &[y, vs]: pos) {
            auto res = seg.all_prod();
            ll sum = res.len - (res.cnt == 0 ? res.sum : 0);
            tot += sum * (y - pre);

            for (auto &q: vs) {
                int delta = (q.op == 0) ? 1 : -1;
                seg.apply(Get(q.x), Get(q.x + q.len), {delta});
            }
            pre = y;
        }

        U(i, 0, m - 2) {
            ll L = temp[i + 1] - temp[i];
            tree_arr[i] = {L, 0, L};
        }
        seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>(tree_arr);

        ll area = 0;
        pre = pos.begin()->fi;
        for (auto &[y, vs]: pos) {
            auto res = seg.all_prod();
            ll sum = res.len - (res.cnt == 0 ? res.sum : 0);
            ll cur = (i128) sum * (y - pre);

            if (area * 2 + cur * 2 >= tot) {
                return (double) pre + (double) (tot - area * 2) / (2.0 * sum);
            }

            area += cur;
            for (auto &q: vs) {
                int delta = (q.op == 0) ? 1 : -1;
                seg.apply(Get(q.x), Get(q.x + q.len), {delta});
            }
            pre = y;
        }

        return (double) pre;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
