#include <bits/stdc++.h>
using namespace std;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
using ll = long long;

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

const int INF = 1e9;

struct S {
    int mx;
};

struct F {
    int lazy;
};

S op(S a, S b) { return {max(a.mx, b.mx)}; }

S e() { return {-INF}; }

S mapping(F f, S x) {
    if (x.mx == -INF)
        return x;
    x.mx += f.lazy;
    return x;
}

F composition(F f, F g) {
    g.lazy += f.lazy;
    return g;
}

F id() { return {0}; }

constexpr int N = 1e5 + 5;

struct Sieve {
    bool is_not_prime[N + 1]{};
    std::vector<int> primes;
    int min_prime_factor[N + 1]{};
    int distinct_factors_count[N + 1]{}; // 不同质因子个数

    int divisor_count[N + 1]{}; // 约数个数
    int cnt_exp[N + 1]{}; // 最小质因子的指数

    Sieve() { init(N); }

    void init(int n) {
        is_not_prime[0] = is_not_prime[1] = true;
        min_prime_factor[0] = min_prime_factor[1] = 0;
        distinct_factors_count[1] = 0;

        divisor_count[1] = 1;
        cnt_exp[1] = 0;

        for (int i = 2; i <= n; ++i) {
            if (!is_not_prime[i]) {
                primes.push_back(i);
                min_prime_factor[i] = i;
                distinct_factors_count[i] = 1;

                cnt_exp[i] = 1;
                divisor_count[i] = 2;
            }

            for (int p: primes) {
                long long x = 1LL * i * p;
                if (x > n)
                    break;
                is_not_prime[i * p] = true;
                min_prime_factor[i * p] = p;

                if (i % p == 0) {
                    distinct_factors_count[i * p] = distinct_factors_count[i];

                    cnt_exp[i * p] = cnt_exp[i] + 1;
                    divisor_count[i * p] = divisor_count[i] / (cnt_exp[i] + 1) * (cnt_exp[i * p] + 1);

                    break;
                } else {
                    distinct_factors_count[i * p] = distinct_factors_count[i] + 1;

                    cnt_exp[i * p] = 1;
                    divisor_count[i * p] = divisor_count[i] * 2;
                }
            }
        }
    }

    [[nodiscard]] bool is_prime(int x) const {
        if (x <= 1 || x > N)
            return false;
        return !is_not_prime[x];
    }
} sieve;

using namespace atcoder;

class Solution {
public:
    vector<int> maximumCount(vector<int> &nums, vector<vector<int>> &queries) {
        int n = nums.size();
        vector<S> tree_arr(n + 1, {0});
        lazy_segtree<S, op, e, F, mapping, composition, id> seg(tree_arr);

        unordered_map<int, set<int>> pos;

        auto upd = [&](int l, int r, int val) {
            if (l < r) {
                seg.apply(l + 1, r + 1, {val});
            }
        };

        auto Add = [&](int idx, int val) {
            if (!sieve.is_prime(val))
                return;

            auto &s = pos[val];
            if (s.empty()) {
                seg.apply(1, n, {1});
                s.insert(idx);
            } else {
                int old_min = *s.begin();
                int old_max = *s.rbegin();

                s.insert(idx);

                if (idx < old_min) {
                    upd(idx, old_min, 1);
                } else if (idx > old_max) {
                    upd(old_max, idx, 1);
                }
            }
        };

        auto Remove = [&](int idx, int val) {
            if (!sieve.is_prime(val))
                return;

            auto &s = pos[val];
            if (s.size() == 1) {
                seg.apply(1, n, {-1});
                s.erase(idx);
            } else {
                int old_min = *s.begin();
                int old_max = *s.rbegin();

                if (idx == old_min) {
                    int mn2 = *next(s.begin());
                    upd(old_min, mn2, -1);
                } else if (idx == old_max) {
                    int mx2 = *prev(s.end(), 2);
                    upd(mx2, old_max, -1);
                }

                s.erase(idx);
            }
        };

        for (int i = 0; i < n; i++) {
            Add(i, nums[i]);
        }

        vector<int> ans;

        for (auto &q: queries) {
            int idx = q[0];
            int val = q[1];
            int old_val = nums[idx];

            if (old_val != val) {
                Remove(idx, old_val);
                nums[idx] = val;
                Add(idx, val);
            }

            ans.push_back(seg.prod(1, n).mx);
        }

        return ans;
    }
};
