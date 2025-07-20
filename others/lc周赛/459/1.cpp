#include "bits/stdc++.h"
using namespace std;
using ll = long long;

vector<ll> arr(65, 0);

ll count(ll x) {
    if (x == 0) return 0;
    ll cnt = 0;
    while (x != 1) {
        x = __builtin_popcountll(x);
        cnt++;
    }
    return cnt;
}

ll count_fast(ll x) {
    if (x == 0) return 0;
    if (x == 1) return 0;
    return 1 + arr[__builtin_popcountll(x)];
}

void init_arr() {
    arr[0] = 0;
    for (ll i = 1; i < 65; i++) {
        arr[i] = count(i);
    }
}

struct Node {
    vector<ll> depth_count;

    Node() : depth_count(7, 0) {}

    Node(ll val) : depth_count(7, 0) {
        ll depth = count_fast(val);
        depth_count[depth]++;
    }

    void merge(const Node& left, const Node& right) {
        for (ll i = 0; i < 7; ++i) {
            depth_count[i] = left.depth_count[i] + right.depth_count[i];
        }
    }
};

class SegmentTree {
private:
    ll _n;
    vector<Node> _tree;

    void _build(const vector<ll>& a, ll node, ll l, ll r) {
        if (l == r) {
            _tree[node] = Node(a[l]);
            return;
        }
        ll m = (l + r) / 2;
        _build(a, node * 2, l, m);
        _build(a, node * 2 + 1, m + 1, r);
        _tree[node].merge(_tree[node * 2], _tree[node * 2 + 1]);
    }

    void _update(ll node, ll l, ll r, ll i, ll new_val) {
        if (l == r) {
            _tree[node] = Node(new_val);
            return;
        }
        ll m = (l + r) / 2;
        if (i <= m) {
            _update(node * 2, l, m, i, new_val);
        } else {
            _update(node * 2 + 1, m + 1, r, i, new_val);
        }
        _tree[node].merge(_tree[node * 2], _tree[node * 2 + 1]);
    }

    ll _query_cnt_k(ll node, ll l, ll r, ll ql, ll qr, ll k) {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr) {
            return (k >= 0 && k < 7) ? _tree[node].depth_count[k] : 0;
        }
        ll m = (l + r) / 2;
        return _query_cnt_k(node * 2, l, m, ql, qr, k) +
               _query_cnt_k(node * 2 + 1, m + 1, r, ql, qr, k);
    }

public:
    SegmentTree(ll n, const vector<ll>& origin_arr) : _n(n), _tree(4 * n) {
        _build(origin_arr, 1, 0, n - 1);
    }

    void update(ll i, ll val) {
        _update(1, 0, _n - 1, i, val);
    }

    ll query_cnt_k(ll ql, ll qr, ll k) {
        return _query_cnt_k(1, 0, _n - 1, ql, qr, k);
    }
};

class Solution {
public:
    vector<int> popcountDepth(vector<long long>& nums, vector<vector<long long>>& queries) {
        init_arr();
        ll n = nums.size();
        SegmentTree st(n, nums);
        vector<int> ans;
        for (const auto& q : queries) {
            if (q[0] == 1) {
                ll a = q[1], b = q[2], c = q[3];
                ans.push_back(st.query_cnt_k(a, b, c));
            } else {
                ll a = q[1], b = q[2];
                st.update(a, b);
            }
        }
        return ans;
    }
};
