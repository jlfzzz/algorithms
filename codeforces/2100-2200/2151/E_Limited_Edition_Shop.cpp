#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
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
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
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
    void prv(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prv(const vector<T> &v, int start_index) {
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
    void rv(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rv(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace utils

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

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
    ll mx, sum, len;
};

struct F {
    ll lazy;
};

S op(S a, S b) { return {max(a.mx, b.mx), a.sum + b.sum, a.len + b.len}; }

S e() { return {-(ll) 4e18, 0, 0}; }

S mapping(F f, S x) {
    x.mx += f.lazy;
    x.sum += x.len * f.lazy;
    return x;
}

F composition(F f, F g) {
    f.lazy += g.lazy;
    return f;
}

F id() { return {0}; }

void init() {}

void solve() {
    int n;
    rd(n);
    vi v1(n), a(n), b(n);
    rv(v1);
    rv(a);
    rv(b);
    map<int, int> pos;
    for (int i = 0; i < n; i++) {
        pos[b[i]] = i;
    }

    vector<S> tree_arr(n + 1);
    for (int i = 0; i <= n; i++) {
        tree_arr[i] = {-(ll) 4e18, 0, 0};
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(tree_arr);
    seg.set(0, {0, 0, 1});

    for (int i = 0; i < n; i++) {
        int cur = a[i];
        int val = v1[cur - 1];
        int nxt = pos[cur] + 1;
        ll mx = seg.prod(0, nxt).mx;
        ll old = seg.get(nxt).mx;
        if (mx > old) {
            seg.set(nxt, {mx, mx, 1});
        }
        seg.apply(0, nxt, {val});
    }

    auto ans = seg.prod(0, n + 1).mx;
    prt(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--) {
        solve();
    }
}
