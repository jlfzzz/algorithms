#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_M = 1e5 + 5;
const int MAX_NODES = MAX_M * 60;

struct Node {
    int ls, rs;
    ll sum, mx, mn;
    ll add;
} tree[MAX_NODES];

struct Result {
    ll sum, mx, mn;
};

int root = 0;
int cnt = 0;

int new_node() {
    ++cnt;
    tree[cnt].ls = tree[cnt].rs = 0;
    tree[cnt].sum = 0;
    tree[cnt].add = 0;
    tree[cnt].mn = 0;
    tree[cnt].mx = 0;
    return cnt;
}

void apply(int &p, ll val, int len) {
    if (!p) {
        p = new_node();
    }
    tree[p].sum += val * len;
    tree[p].mx += val;
    tree[p].mn += val;
    tree[p].add += val;
}

void pushdown(int p, int l, int r) {
    if (tree[p].add == 0)
        return;
    int mid = l + (r - l) / 2;
    apply(tree[p].ls, tree[p].add, mid - l + 1);
    apply(tree[p].rs, tree[p].add, r - mid);
    tree[p].add = 0;
}

void pushup(int p) {
    tree[p].sum = tree[tree[p].ls].sum + tree[tree[p].rs].sum;
    tree[p].mx = max(tree[tree[p].ls].mx, tree[tree[p].rs].mx);
    tree[p].mn = min(tree[tree[p].ls].mn, tree[tree[p].rs].mn);
}

void update(int &p, int l, int r, int ql, int qr, int val) {
    if (!p)
        p = new_node();

    if (ql <= l && r <= qr) {
        apply(p, val, r - l + 1);
        return;
    }
    pushdown(p, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid)
        update(tree[p].ls, l, mid, ql, qr, val);
    if (qr > mid)
        update(tree[p].rs, mid + 1, r, ql, qr, val);
    pushup(p);
}

Result query_all(int p, int l, int r, int ql, int qr) {
    if (!p)
        return {0, 0, 0};

    if (ql <= l && r <= qr) {
        return {tree[p].sum, tree[p].mx, tree[p].mn};
    }

    pushdown(p, l, r);
    int mid = l + (r - l) / 2;

    Result res = {0, (ll) -4e18, (ll) 4e18};
    bool found = false;

    if (ql <= mid) {
        res = query_all(tree[p].ls, l, mid, ql, qr);
        found = true;
    }
    if (qr > mid) {
        Result right = query_all(tree[p].rs, mid + 1, r, ql, qr);
        if (!found) {
            res = right;
        } else {
            res.sum += right.sum;
            res.mx = max(res.mx, right.mx);
            res.mn = min(res.mn, right.mn);
        }
    }
    return res;
}
