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
    long long sum;
    long long max_pref;
    long long max_suf;
    long long max_sub;
    long long min_pref;
    long long min_suf;
    long long min_sub;
};

struct F {
    int dummy;
};

static const long long INF64 = (long long) 4e18;

S e() { return {0, -INF64, -INF64, -INF64, INF64, INF64, INF64}; }

S single(long long w) { return {w, w, w, w, w, w, w}; }

S op(S a, S b) {
    if (a.max_sub == -INF64)
        return b;
    if (b.max_sub == -INF64)
        return a;
    S c{};
    c.sum = a.sum + b.sum;
    c.max_pref = max(a.max_pref, a.sum + b.max_pref);
    c.max_suf = max(b.max_suf, b.sum + a.max_suf);
    c.max_sub = max({a.max_sub, b.max_sub, a.max_suf + b.max_pref});
    c.min_pref = min(a.min_pref, a.sum + b.min_pref);
    c.min_suf = min(b.min_suf, b.sum + a.min_suf);
    c.min_sub = min({a.min_sub, b.min_sub, a.min_suf + b.min_pref});
    return c;
}

S mapping(F, S x) { return x; }

F composition(F, F g) { return g; }

F id() { return {0}; }

S revS(S x) {
    swap(x.max_pref, x.max_suf);
    swap(x.min_pref, x.min_suf);
    return x;
}

class HLD {
public:
    int n, timer{};
    vector<vector<int>> g;
    vector<int> depth, parent, heavy, head, pos, sz;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg;

    explicit HLD(int n) :
        n(n), g(n + 1), depth(n + 1), parent(n + 1), heavy(n + 1), head(n + 1), pos(n + 1), sz(n + 1),
        seg(vector<S>(n + 2, e())) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int dfs1(int u, int fa) {
        sz[u] = 1;
        parent[u] = fa;
        heavy[u] = -1;
        depth[u] = (fa == -1 ? 0 : depth[fa] + 1);
        for (int v: g[u]) {
            if (v == fa)
                continue;
            sz[u] += dfs1(v, u);
            if (heavy[u] == -1 || sz[v] > sz[heavy[u]])
                heavy[u] = v;
        }
        return sz[u];
    }

    void dfs2(int u, int top) {
        head[u] = top;
        pos[u] = ++timer;
        if (heavy[u] != -1)
            dfs2(heavy[u], top);
        for (int v: g[u]) {
            if (v == parent[u] || v == heavy[u])
                continue;
            dfs2(v, v);
        }
    }

    void build(int root) {
        timer = 0;
        dfs1(root, -1);
        dfs2(root, root);
    }

    void point_set(int u, long long w) { seg.set(pos[u], single(w)); }

    S query_path(int u, int v) {
        S left = e(), right = e();
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                S cur = seg.prod(pos[head[u]], pos[u] + 1);
                left = op(left, revS(cur));
                u = parent[head[u]];
            } else {
                S cur = seg.prod(pos[head[v]], pos[v] + 1);
                right = op(cur, right);
                v = parent[head[v]];
            }
        }
        if (depth[u] > depth[v]) {
            S cur = seg.prod(pos[v], pos[u] + 1);
            left = op(left, revS(cur));
        } else {
            S cur = seg.prod(pos[u], pos[v] + 1);
            right = op(cur, right);
        }
        return op(left, right);
    }
};


void init() {}

struct Op1 {
    int v;
    int x;
    int id;
};
struct Op2 {
    int u;
    int v;
    int k;
    int id;
};

void solve() {
    int n;
    cin >> n;

    vector<char> typ(n);
    vector<Op1> adds;
    vector<Op2> asks;

    int sz = 1;
    vector<pair<int, int>> edges;
    vector<pair<int, int>> pendingAdds;
    vector<tuple<int, int, int>> pendingAsks;

    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        typ[i] = op;
        if (op == '+') {
            int v, x;
            cin >> v >> x;
            ++sz;
            edges.emplace_back(v, sz);
            pendingAdds.emplace_back(sz, x);
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            pendingAsks.emplace_back(u, v, k);
        }
    }

    int N = sz;
    HLD hld(N);
    for (auto [u, v]: edges) {
        hld.add_edge(u, v);
    }
    hld.build(1);

    hld.point_set(1, 1);

    vector<string> out;

    sz = 1;
    size_t ia = 0, iq = 0;
    for (int i = 0; i < n; i++) {
        if (typ[i] == '+') {
            int id = (int) pendingAdds[ia].first;
            int x = (int) pendingAdds[ia].second;
            ia++;
            hld.point_set(id, x);
            sz++;
        } else {
            auto [u, v, k] = pendingAsks[iq++];
            if (k == 0) {
                out.emplace_back("YES");
                continue;
            }
            S res = hld.query_path(u, v);
            long long up = res.max_sub;
            long long down = -res.min_sub;
            bool ok = false;
            if (k > 0)
                ok = (k <= up);
            else
                ok = (-k <= down);
            out.emplace_back(ok ? "YES" : "NO");
        }
    }

    for (auto &s: out)
        cout << s << '\n';
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
