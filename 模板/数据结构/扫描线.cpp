#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class SegTree {
private:
    struct Node {
        int cnt = 0;
        int len = 0;
    };
    vector<int> ys;
    vector<Node> tree;
    int n;

    void pushup(int o, int l, int r) {
        if (tree[o].cnt > 0)
            tree[o].len = ys[r] - ys[l];
        else if (r - l == 1) // 叶子
            tree[o].len = 0;
        else
            tree[o].len = tree[o * 2].len + tree[o * 2 + 1].len;
    }

    void update(int o, int l, int r, int ql, int qr, int val) {
        if (ql >= r || qr <= l)
            return;
        if (ql <= l && r <= qr)
            tree[o].cnt += val;
        else {
            int m = (l + r) / 2;
            update(o * 2, l, m, ql, qr, val);
            update(o * 2 + 1, m, r, ql, qr, val);
        }
        pushup(o, l, r);
    }

public:
    explicit SegTree(const vector<int> &_ys) {
        ys = _ys;
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        n = ys.size() - 1;
        tree.assign(4 * n, Node{0, 0});
    }

    void update(int y1, int y2, int val) {
        int l = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
        int r = lower_bound(ys.begin(), ys.end(), y2) - ys.begin();
        update(1, 0, n, l, r, val);
    }

    [[nodiscard]] int query() const { return tree[1].len; }
};
