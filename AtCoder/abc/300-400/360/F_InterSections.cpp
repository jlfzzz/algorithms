#include <bits/stdc++.h>
using namespace std;

// --------- Minimal ACL-style Lazy Segtree (range add, range max + min index) ----------
namespace atcoder {
    namespace internal {
        unsigned int bit_ceil(unsigned int n) {
            unsigned int x = 1;
            while (x < n)
                x <<= 1;
            return x;
        }
        int countr_zero(unsigned int n) { return __builtin_ctz(n); }
    } // namespace internal

    template<class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
    struct lazy_segtree {
        int _n = 0, size = 1, log = 0;
        vector<S> d;
        vector<F> lz;

        lazy_segtree() {}
        explicit lazy_segtree(int n) : lazy_segtree(vector<S>(n, e())) {}
        explicit lazy_segtree(const vector<S> &v) { init(v); }

        void init(const vector<S> &v) {
            _n = (int) v.size();
            size = (int) internal::bit_ceil((unsigned int) _n);
            log = internal::countr_zero((unsigned int) size);
            d.assign(2 * size, e());
            lz.assign(size, id());
            for (int i = 0; i < _n; i++)
                d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--)
                update(i);
        }

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

        // apply on [l, r)
        void apply(int l, int r, F f) {
            if (l >= r)
                return;
            l += size;
            r += size;
            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l)
                    push(l >> i);
                if (((r >> i) << i) != r)
                    push((r - 1) >> i);
            }
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
            for (int i = 1; i <= log; i++) {
                if (((l >> i) << i) != l)
                    update(l >> i);
                if (((r >> i) << i) != r)
                    update((r - 1) >> i);
            }
        }

        // prod on [l, r)
        S prod(int l, int r) {
            if (l >= r)
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
    };
} // namespace atcoder

// ---------------- Problem solution ----------------
static const int MAXR = 1'000'000'000;
static const int MINX = 1;
static const int MAXX = MAXR; // x = l+1, l<=1e9-1

struct S {
    int mx; // max value
    int idx; // smallest index achieving mx
};
struct F {
    int add;
};

S opS(S a, S b) {
    if (a.mx != b.mx)
        return (a.mx > b.mx ? a : b);
    return (a.idx < b.idx ? a : b);
}
S eS() { return {INT_MIN / 4, INT_MAX}; }
S mapping(F f, S x) { return {x.mx + f.add, x.idx}; }
F composition(F f, F g) { return {f.add + g.add}; }
F idF() { return {0}; }

struct Event {
    int l, r; // range on r-axis (inclusive, but we will convert to [lidx, ridx+1))
    int delta; // +1 / -1
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    map<int, vector<Event>> ev; // key = x = l+1
    vector<int> rcoords;
    vector<int> xcoords;

    auto add_event = [&](int x, int l, int r, int delta) {
        if (delta == 0)
            return;
        if (x < MINX || x > MAXX)
            return;

        l = max(l, 0);
        r = min(r, MAXR);
        if (l > r)
            return;

        ev[x].push_back({l, r, delta});
        rcoords.push_back(l);
        rcoords.push_back(r);
        xcoords.push_back(x);
    };

    for (int i = 0; i < N; i++) {
        long long L, R;
        cin >> L >> R;

        // Type A: l < L < r < R
        // With x = l+1: active for x <= L
        // r-range: [L+1, R-1]
        long long aL = L + 1;
        long long aR = R - 1;
        if (L >= 1 && aL <= aR) {
            add_event(1, (int) aL, (int) aR, +1); // start at x=1
            add_event((int) (L + 1), (int) aL, (int) aR, -1); // remove at x=L+1
        }

        // Type B: L < l < R < r
        // With x = l+1: active for x in [L+2, R]
        // r-range: [R+1, MAXR]
        long long bStart = L + 2;
        long long bEnd = R; // last x where still active
        long long bL = R + 1;
        if (bStart <= bEnd && bL <= MAXR) {
            add_event((int) bStart, (int) bL, MAXR, +1); // add at x=L+2
            add_event((int) (R + 1), (int) bL, MAXR, -1); // remove at x=R+1
        }
    }

    // Always consider x=1 (i.e., l=0)
    xcoords.push_back(1);
    rcoords.push_back(0);
    rcoords.push_back(MAXR);

    sort(xcoords.begin(), xcoords.end());
    xcoords.erase(unique(xcoords.begin(), xcoords.end()), xcoords.end());

    // Ensure r can be exactly x (tie-break on minimal r)
    for (int x: xcoords) {
        if (0 <= x && x <= MAXR)
            rcoords.push_back(x);
    }

    sort(rcoords.begin(), rcoords.end());
    rcoords.erase(unique(rcoords.begin(), rcoords.end()), rcoords.end());

    auto getR = [&](int v) { return (int) (lower_bound(rcoords.begin(), rcoords.end(), v) - rcoords.begin()); };

    int M = (int) rcoords.size();
    vector<S> init(M);
    for (int i = 0; i < M; i++)
        init[i] = {0, i};
    atcoder::lazy_segtree<S, opS, eS, F, mapping, composition, idF> seg(init);

    auto apply_range = [&](int l, int r, int delta) {
        if (l > r)
            return;
        int L = getR(l);
        int R = getR(r);
        seg.apply(L, R + 1, F{delta});
    };

    int bestF = INT_MIN;
    int bestL = 0, bestR = 1;

    for (int x: xcoords) {
        // apply all events happening at this x (must be BEFORE evaluating x)
        auto it = ev.find(x);
        if (it != ev.end()) {
            for (auto &e: it->second) {
                apply_range(e.l, e.r, e.delta);
            }
        }

        // query r >= x
        int pos = getR(x);
        if (pos >= M)
            continue;
        S res = seg.prod(pos, M);

        int l = x - 1;
        int r = rcoords[res.idx];
        int f = res.mx;

        if (f > bestF || (f == bestF && (l < bestL || (l == bestL && r < bestR)))) {
            bestF = f;
            bestL = l;
            bestR = r;
        }
    }

    cout << bestL << " " << bestR << "\n";
    return 0;
}
