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
    int len;
};

struct F {
    long long add;
};

S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }

S e() { return {0, 0}; }

S mapping(F f, S x) { return {x.sum + f.add * x.len, x.len}; }

F composition(F f, F g) { return {f.add + g.add}; }

F id() { return {0}; }

// S 就是 Node，结构体
// F 是 lazy 的结构体
// op 就是maintain，pushup，合并节点
// e 就是无效值，例如0，或者求最大值的时候一定要设置会为最小，反之
// mapping 就是用lazy去更新
// composition 就是lazy合并，参数f是新lazy，g是旧lazy。记得优先级
// id 就是无效的lazy，例如-1

// 构造函数记得传入 S 数组 tree_arr
// 查询是 左闭右开！
// max_right 是传入一个索引，左起点，从它开始一直往右找一个return true的
// min_left 是传入一个索引，右起点，从它开始一直往左找一个return true的

// 删除全局段树，使用类内实例

class HLD {
public:
    int n, timer{};
    vector<vector<int>> g;
    vector<int> depth, parent, heavy, head, pos, sz;
    vector<long long> node_value;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg;

    explicit HLD(int n) :
        n(n), g(n + 1), depth(n + 1), parent(n + 1), heavy(n + 1), head(n + 1), pos(n + 1), sz(n + 1),
        node_value(n + 1, 0), seg(vector<S>(n + 2, e())) {}

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
        vector<S> base(timer + 2, e());
        for (int u = 1; u <= n; u++) {
            base[pos[u]] = {node_value[u], 1};
        }
        seg = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>(base);
    }

    void set_node(int u, long long v) { node_value[u] = v; }

    long long path_sum(int u, int v) {
        long long res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            S cur = seg.prod(pos[head[u]], pos[u] + 1);
            res += cur.sum;
            u = parent[head[u]];
        }
        if (depth[u] < depth[v])
            swap(u, v);
        S cur = seg.prod(pos[v], pos[u] + 1);
        res += cur.sum;
        return res;
    }

    void path_add(int u, int v, int val) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            seg.apply(pos[head[u]], pos[u] + 1, {val});
            u = parent[head[u]];
        }
        if (depth[u] < depth[v])
            swap(u, v);
        seg.apply(pos[v], pos[u] + 1, {val});
    }

    long long subtree_sum(int u) {
        S cur = seg.prod(pos[u], pos[u] + sz[u]);
        return cur.sum;
    }

    void subtree_add(int u, int val) { seg.apply(pos[u], pos[u] + sz[u], {val}); }

    void point_set(int u, long long v) { seg.set(pos[u], {v, 1}); }
};
