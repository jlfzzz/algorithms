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

namespace io {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
    }

    template<typename... Args>
    void prt(const Args &...args) {
        ((cout << args << " "), ...);
        cout << "\n";
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

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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
} // namespace io

using namespace io;

struct Node {
    ll sum, mx;
    int l, r;
};

class SegmentTree {
private:
    vector<Node> tree;
    vector<ll> arr;
    int n;

    void build(int idx, int l, int r) {
        tree[idx].l = l, tree[idx].r = r;
        if (l == r) {
            tree[idx].sum = tree[idx].mx = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);
        push_up(idx);
    }

    void push_up(int idx) {
        tree[idx].sum = tree[idx * 2].sum + tree[idx * 2 + 1].sum;
        tree[idx].mx = max(tree[idx * 2].mx, tree[idx * 2 + 1].mx);
    }

public:
    SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        arr = nums;
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    // 区间开平方
    void sqrt_update(int idx, int l, int r) {
        if (tree[idx].mx <= 1)
            return; // 关键优化：整个区间都是0或1，不需要开平方

        if (tree[idx].l == tree[idx].r) {
            // 叶子节点，直接开平方
            if (tree[idx].sum > 1) {
                tree[idx].sum = tree[idx].mx = (ll) sqrt(tree[idx].sum);
            }
            return;
        }

        int mid = (tree[idx].l + tree[idx].r) / 2;
        if (l <= mid)
            sqrt_update(idx * 2, l, min(r, mid));
        if (r > mid)
            sqrt_update(idx * 2 + 1, max(l, mid + 1), r);

        push_up(idx);
    }

    // 区间求和
    ll query_sum(int idx, int l, int r) {
        if (l <= tree[idx].l && tree[idx].r <= r) {
            return tree[idx].sum;
        }

        int mid = (tree[idx].l + tree[idx].r) / 2;
        ll res = 0;
        if (l <= mid)
            res += query_sum(idx * 2, l, min(r, mid));
        if (r > mid)
            res += query_sum(idx * 2 + 1, max(l, mid + 1), r);
        return res;
    }

    // 封装接口
    void sqrt_range(int l, int r) { sqrt_update(1, l, r); }

    ll sum_range(int l, int r) { return query_sum(1, l, r); }
};

void solve() {
    int n;
    rd(n);

    vector<ll> arr(n);
    For(i, n) { rd(arr[i]); }

    SegmentTree seg(arr);

    int m;
    rd(m);
    while (m--) {
        ll k, l, r;
        rd(k, l, r);

        if (l > r)
            swap(l, r);
        l--;
        r--;

        if (k == 0) {
            seg.sqrt_range(l, r);
        } else {
            ll sum = seg.sum_range(l, r);
            prt(sum);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
