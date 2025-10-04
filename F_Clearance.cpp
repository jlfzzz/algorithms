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
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace io {
    inline ostream &operator<<(ostream &os, i128 value) {
        if (value == 0) {
            os << 0;
            return os;
        }
        bool is_negative = value < 0;
        if (is_negative)
            value = -value;
        string digits;
        while (value > 0) {
            int digit = value % 10;
            digits.push_back(char('0' + digit));
            value /= 10;
        }
        if (is_negative)
            os << '-';
        for (int i = (int) digits.size() - 1; i >= 0; --i)
            os << digits[i];
        return os;
    }
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

int Multitest = 0;

void init() {}

struct Node {
    i128 sum;
    int min_val;
    int max_val;
    int lazy;
    bool zero;
    Node() : sum(0), min_val(0), max_val(0), lazy(0), zero(false) {}
};

class SegmentTree {
private:
    int n;
    vector<Node> tree;
    vector<int> arr;

    void build(int node, int l, int r) {
        if (l == r) {
            tree[node].sum = arr[l];
            tree[node].min_val = arr[l];
            tree[node].max_val = arr[l];
            tree[node].lazy = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        merge(node);
    }

    void merge(int node) {
        tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
        tree[node].min_val = min(tree[node * 2].min_val, tree[node * 2 + 1].min_val);
        tree[node].max_val = max(tree[node * 2].max_val, tree[node * 2 + 1].max_val);
    }

    void apply(int node, int l, int r, int val) {
        tree[node].sum -= (i128) val * (r - l + 1);
        tree[node].min_val -= val;
        tree[node].max_val -= val;
        tree[node].lazy += val;
    }

    void apply_zero(int node, int l, int r) {
        tree[node].sum = 0;
        tree[node].min_val = 0;
        tree[node].max_val = 0;
        tree[node].lazy = 0;
        tree[node].zero = true;
    }

    void push_down(int node, int l, int r) {
        if (l == r)
            return;
        int mid = (l + r) / 2;
        if (tree[node].zero) {
            apply_zero(node * 2, l, mid);
            apply_zero(node * 2 + 1, mid + 1, r);
            tree[node].zero = false;
        }
        if (tree[node].lazy != 0) {
            apply(node * 2, l, mid, tree[node].lazy);
            apply(node * 2 + 1, mid + 1, r, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }

    i128 update_range(int node, int l, int r, int ql, int qr, int k) {
        if (qr < l || ql > r)
            return (i128) 0;
        if (k == 0)
            return (i128) 0;
        if (tree[node].max_val == 0)
            return (i128) 0;

        if (ql <= l && r <= qr) {
            if (tree[node].min_val >= k) {
                apply(node, l, r, k);
                return (i128) k * (r - l + 1);
            }
            if (tree[node].max_val <= k) {
                i128 bought = tree[node].sum;
                apply_zero(node, l, r);
                return bought;
            }
        }

        push_down(node, l, r);
        int mid = (l + r) / 2;
        i128 bought = 0;
        if (ql <= mid) {
            bought += update_range(node * 2, l, mid, ql, qr, k);
        }
        if (qr > mid) {
            bought += update_range(node * 2 + 1, mid + 1, r, ql, qr, k);
        }
        merge(node);
        return bought;
    }

public:
    SegmentTree(const vector<int> &a) {
        n = a.size();
        arr = a;
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    i128 buy(int l, int r, int k) { return update_range(1, 0, n - 1, l - 1, r - 1, k); }
};


void solve() {
    int n;
    rd(n);
    vector<int> a(n);
    rd_vec(a);
    SegmentTree seg(a);
    int q;
    rd(q);
    for (int i = 0; i < q; i++) {
        int l, r, k;
        rd(l, r, k);
        prt(seg.buy(l, r, k));
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
