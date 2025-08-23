#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int sum1;
    bool lazy;
};

class Seg {
public:
    vector<Node> tree;
    int n_;

    Seg(int n, vector<int> &v1) : tree(4 * n), n_(n) {
        auto build = [&](this auto &&build, int o, int l, int r) -> void {
            if (l == r) {
                tree[o].sum1 = v1[l];
                tree[o].lazy = false;
                return;
            }
            int m = (l + r) / 2;
            build(o * 2, l, m);
            build(o * 2 + 1, m + 1, r);
            tree[o].sum1 = tree[o * 2].sum1 + tree[o * 2 + 1].sum1;
            tree[o].lazy = false;
        };
        build(1, 0, n - 1);
    }

    void push(int o, int l, int r) {
        if (tree[o].lazy) {
            int len = r - l + 1;
            tree[o].sum1 = len - tree[o].sum1;
            if (l != r) {
                tree[o * 2].lazy = !tree[o * 2].lazy;
                tree[o * 2 + 1].lazy = !tree[o * 2 + 1].lazy;
            }
            tree[o].lazy = false;
        }
    }

    void update(int o, int l, int r, int L, int R) {
        push(o, l, r);
        if (l > R || r < L)
            return;
        if (l >= L && r <= R) {
            tree[o].lazy = true;
            push(o, l, r);
            return;
        }
        int m = (l + r) / 2;
        update(o * 2, l, m, L, R);
        update(o * 2 + 1, m + 1, r, L, R);
        tree[o].sum1 = tree[o * 2].sum1 + tree[o * 2 + 1].sum1;
    }
};

class Solution {
public:
    vector<long long> handleQuery(vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &queries) {
        int n = nums1.size();
        vector<long long> ans;
        Seg seg(n, nums1);
        ll total = accumulate(nums2.begin(), nums2.end(), 0LL);

        for (auto &q: queries) {
            int op = q[0];
            if (op == 1) {
                int l = q[1], r = q[2];
                seg.update(1, 0, n - 1, l, r);
            } else if (op == 2) {
                ll p = q[1];
                total += p * seg.tree[1].sum1;
            } else {
                ans.push_back(total);
            }
        }
        return ans;
    }
};
