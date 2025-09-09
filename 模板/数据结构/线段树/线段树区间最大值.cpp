#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct SegmentTreeNode {
    ll val;
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    SegmentTreeNode merge(const SegmentTreeNode &left, const SegmentTreeNode &right) {
        return {max(left.val, right.val)};
    }

    void build(const vector<ll> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = {nums[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node].val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return LLONG_MIN;
        if (ql <= l && r <= qr)
            return tree[node].val;
        int mid = (l + r) / 2;
        return max(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
    }

public:
    explicit SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        tree.resize(4 * n + 5);
        build(nums, 1, 0, n - 1);
    }

    explicit SegmentTree(int n) : n(n), tree(4 * n + 5) {}

    void update(int idx, ll val) { update(1, 0, n - 1, idx, val); }

    ll rangeMax(int l, int r) { return query(1, 0, n - 1, l, r); }

    ll getValue(int idx) { return rangeMax(idx, idx); }
};
