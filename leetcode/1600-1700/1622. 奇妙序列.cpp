#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;
const int N = 1e5 + 5;

struct Node {
    long long val, add, mul;
    Node() : val(0), add(0), mul(1) {}
};

struct Fancy {
    int n;
    vector<Node> tree;

    Fancy() {
        n = 0;
        tree.assign(4 * N + 500, Node());
    }

    void push(int o, int l, int r) {
        Node &node = tree[o];
        if (node.mul != 1 || node.add != 0) {
            node.val = (node.val * node.mul % MOD + (r - l + 1) * node.add % MOD) % MOD;
            if (l != r) {
                for (int c: {o * 2, o * 2 + 1}) {
                    tree[c].mul = tree[c].mul * node.mul % MOD;
                    tree[c].add = (tree[c].add * node.mul % MOD + node.add) % MOD;
                }
            }
            node.mul = 1;
            node.add = 0;
        }
    }

    void range_add(int o, int l, int r, int L, int R, int val) {
        if (l > R || r < L || L > R)
            return;
        if (l >= L && r <= R) {
            tree[o].add = (tree[o].add + val) % MOD;
            push(o, l, r);
            return;
        }
        push(o, l, r);
        int m = (l + r) / 2;
        if (L <= m)
            range_add(o * 2, l, m, L, R, val);
        if (R > m)
            range_add(o * 2 + 1, m + 1, r, L, R, val);
        tree[o].val = (tree[o * 2].val + tree[o * 2 + 1].val) % MOD;
    }

    void range_mul(int o, int l, int r, int L, int R, int val) {
        if (l > R || r < L || L > R)
            return;
        if (l >= L && r <= R) {
            // push(o, l, r);
            tree[o].mul = tree[o].mul * val % MOD;
            // tree[o].add = tree[o].add * val % MOD;
            push(o, l, r);
            return;
        }
        push(o, l, r);
        int m = (l + r) / 2;
        if (L <= m)
            range_mul(o * 2, l, m, L, R, val);
        if (R > m)
            range_mul(o * 2 + 1, m + 1, r, L, R, val);
        tree[o].val = (tree[o * 2].val + tree[o * 2 + 1].val) % MOD;
    }

    int query(int o, int l, int r, int i) {
        push(o, l, r);
        if (l == r)
            return tree[o].val % MOD;
        int m = (l + r) / 2;
        if (i <= m)
            return query(o * 2, l, m, i);
        return query(o * 2 + 1, m + 1, r, i);
    }

    void append(int val) {
        range_add(1, 0, N, n, n, val);
        n++;
    }

    void addAll(int inc) {
        if (n > 0)
            range_add(1, 0, N, 0, n - 1, inc);
    }

    void multAll(int m) {
        if (n > 0)
            range_mul(1, 0, N, 0, n - 1, m);
    }

    int getIndex(int idx) {
        if (idx >= n)
            return -1;
        return query(1, 0, N, idx);
    }
};
