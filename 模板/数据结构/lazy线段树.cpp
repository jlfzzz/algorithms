#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// lazy

struct SegmentTreeNode {
    ll val, lazy;
    SegmentTreeNode(ll v = 0, ll lz = 0) : val(v), lazy(lz) {}
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    void apply(int node, int l, int r, ll val) {
        tree[node].val += val * (r - l + 1);
        tree[node].lazy += val;
    }

    void pushDown(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            int mid = (l + r) / 2;
            apply(node * 2, l, mid, tree[node].lazy);
            apply(node * 2 + 1, mid + 1, r, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }

    void build(const vector<ll> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = {nums[l], 0};
            return;
        }
        int mid = (l + r) / 2;
        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);
        tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node].val += val;
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        rangeAdd(node * 2, l, mid, ql, qr, val);
        rangeAdd(node * 2 + 1, mid + 1, r, ql, qr, val);
        tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[node].val;
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        return query(node * 2, l, mid, ql, qr) + query(node * 2 + 1, mid + 1, r, ql, qr);
    }

public:
    SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    void update(int idx, ll val) { update(1, 0, n - 1, idx, val); }

    void rangeAdd(int l, int r, ll val) { rangeAdd(1, 0, n - 1, l, r, val); }

    ll rangeSum(int l, int r) { return query(1, 0, n - 1, l, r); }

    ll getValue(int idx) { return rangeSum(idx, idx); }
};
