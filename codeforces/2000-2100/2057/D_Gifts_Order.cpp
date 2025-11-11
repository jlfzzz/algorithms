#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
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
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

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

// DDP
namespace DDP {
    using Matrix = array<array<ll, 4>, 4>;

    struct S {
        Matrix mat;
    };

    struct F {
        int lazy;
    };

    S op(S a, S b) {
        Matrix mat;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mat[i][j] = -INF;
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    mat[i][j] = max(mat[i][j], b.mat[i][k] + a.mat[k][j]);
                }
            }
        }
        return {mat};
    }

    S e() {
        Matrix mat;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mat[i][j] = -INF;
            }
        }
        for (int i = 0; i < 4; i++) {
            mat[i][i] = 0;
        }
        return {mat};
    }

    S mapping(F f, S x) { return x; }

    F composition(F f, F g) { return f; }

    F id() { return {0}; }

    constexpr int N = 1e6 + 5;

    int Multitest = 1;

    void init() {}

    void solve() {
        int n, q;
        rd(n, q);

        vl a(n + 1);
        rv(a, 1);

        vector<S> tree_arr(n + 1);
        {
            Matrix idm;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    idm[i][j] = -INF;
                }
            }
            for (int i = 0; i < 4; i++) {
                idm[i][i] = 0;
            }
            tree_arr[0] = {idm};
        }
        for (int i = 1; i <= n; i++) {
            ll x = a[i];
            ll P = x + i;
            ll Mv = x - i;
            Matrix mat;
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    mat[j][k] = -INF;
                }
            }

            mat[0][0] = 0;
            mat[1][1] = 0;
            mat[2][2] = 0;
            mat[3][3] = 0;
            mat[1][0] = P;
            mat[2][1] = -P;
            mat[3][0] = -Mv;
            mat[2][3] = Mv;
            tree_arr[i] = {mat};
        }
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(tree_arr);

        {
            S root = seg.all_prod();
            ll ans = max(0LL, root.mat[2][0]);
            prt(ans);
        }

        while (q--) {
            int p, x;
            rd(p, x);

            a[p] = x;
            ll i = p;
            ll P = x + i;
            ll Mv = x - i;
            Matrix mat;
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    mat[j][k] = -INF;
                }
            }
            mat[0][0] = 0;
            mat[1][1] = 0;
            mat[2][2] = 0;
            mat[3][3] = 0;
            mat[1][0] = P;
            mat[2][1] = -P;
            mat[3][0] = -Mv;
            mat[2][3] = Mv;
            seg.set(p, {mat});
            {
                S root = seg.all_prod();
                ll ans = max(0LL, root.mat[2][0]);
                prt(ans);
            }
        }
    }
} // namespace DDP

// 线段树
struct S {
    ll lmx, rmn, lmn, rmx, best;
};

struct F {
    ll lazy;
};

S op(S a, S b) {
    S res;
    res.lmn = min(a.lmn, b.lmn);
    res.lmx = max(a.lmx, b.lmx);
    res.rmn = min(a.rmn, b.rmn);
    res.rmx = max(a.rmx, b.rmx);
    res.best = max({a.best, b.best, a.lmx - b.rmn, b.rmx - a.lmn});
    return res;
}

S e() { return {-INF, INF, INF, -INF, -INF}; }

S mapping(F f, S x) { return x; }

F composition(F f, F g) { return f; }

F id() { return {0}; }

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n, q;
    rd(n, q);

    vl a(n + 1);
    rv(a, 1);

    vector<S> tree_arr(n);
    for (int i = 1; i <= n; i++) {
        ll x = a[i] + i;
        ll y = a[i] - i;
        tree_arr[i - 1] = {x, x, y, y, 0};
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(tree_arr);

    prt(seg.all_prod().best);

    while (q--) {
        int p, x;
        rd(p, x);

        a[p] = x;
        ll t1 = x + p;
        ll t2 = x - p;
        S res{t1, t1, t2, t2, 0};
        seg.set(p - 1, res);
        prt(seg.all_prod().best);
    }
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
