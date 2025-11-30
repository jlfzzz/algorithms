#include "bits/stdc++.h"
using namespace std;
using ll = long long;


struct Node {
    ll val = 0;
};

class PST {
private:
    int n, ts;
    std::vector<int> lc, rc;
    std::vector<Node> tree;

    void newnode(int pre, int cur) {
        lc[cur] = lc[pre];
        rc[cur] = rc[pre];
        tree[cur] = tree[pre];
    }

    Node merge(const Node &left, const Node &right) { return Node{left.val + right.val}; }

    int _build(const std::vector<int> &arr, int l, int r) {
        int cur = ++ts;
        if (l == r) {
            tree[cur] = Node{arr[l]};
            return cur;
        }
        int m = (l + r) / 2;
        lc[cur] = _build(arr, l, m);
        rc[cur] = _build(arr, m + 1, r);
        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _update(int pre, int l, int r, int pos, ll val) {
        int cur = ++ts;
        newnode(pre, cur);
        if (l == r) {
            tree[cur].val += val;
            return cur;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            lc[cur] = _update(lc[pre], l, m, pos, val);
        else
            rc[cur] = _update(rc[pre], m + 1, r, pos, val);

        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _query(int cur, int pre, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return tree[cur].val - tree[pre].val;
        int m = (l + r) / 2;
        return _query(lc[cur], lc[pre], l, m, ql, qr) + _query(rc[cur], rc[pre], m + 1, r, ql, qr);
    }

    int _kth(int cur, int pre, int l, int r, int k) {
        if (l == r)
            return l;
        int cnt = tree[lc[cur]].val - tree[lc[pre]].val;
        int m = (l + r) / 2;
        if (k <= cnt)
            return _kth(lc[cur], lc[pre], l, m, k);
        else
            return _kth(rc[cur], rc[pre], m + 1, r, k - cnt);
    }

public:
    PST(int n) : n(n), ts(0), lc(40 * n + 5), rc(40 * n + 5), tree(40 * n + 5) {}

    int build(const std::vector<int> &arr) { return _build(arr, 1, n); }

    int update(int pre_version, int pos, ll val) { return _update(pre_version, 1, n, pos, val); }

    int query(int cur_version, int pre_version, int l, int r) { return _query(cur_version, pre_version, 1, n, l, r); }

    int kth(int cur_version, int pre_version, int k) { return _kth(cur_version, pre_version, 1, n, k); }
};
