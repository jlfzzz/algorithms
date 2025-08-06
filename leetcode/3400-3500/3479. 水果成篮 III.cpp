//
// Created by 123 on 25-7-24.
//
#include <bit>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
const ll MOD2 = 4611686018427387847;

class St {
public:
    vector<int> tree;
    St(int n) { tree.resize(2 << (bit_width((unsigned) n))); }

    void update(int o, int l, int r, int i, int val) {
        if (l == r) {
            tree[o] = val;
            return;
        }
        int m = l + (r - l) / 2;
        if (i <= m) {
            update(o * 2, l, m, i, val);
        } else {
            update(o * 2 + 1, m + 1, r, i, val);
        }
        tree[o] = max(tree[o * 2], tree[o * 2 + 1]);
    }

    int query(int o, int l, int r, int target) {
        if (tree[o] < target) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = l + (r - l) / 2;
        int res = query(o * 2, l, m, target);
        if (res < 0) {
            res = query(o * 2 + 1, m + 1, r, target);
        }
        return res;
    }
};


class Solution {
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets) {
        int n = fruits.size();
        St st(n);
        for (int i = 0; i < n; i++) {
            st.update(1, 0, n - 1, i, baskets[i]);
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int f = fruits[i];
            int j = st.query(1, 0, n - 1, f);
            if (j < 0) {
                ans++;
            } else {
                st.update(1, 0, n - 1, j, 0);
            }
        }
        return ans;
    }
};






class SegmentTree {
    vector<int> mx;

    void maintain(int o) { mx[o] = max(mx[o * 2], mx[o * 2 + 1]); }

    // 初始化线段树
    void build(const vector<int> &a, int o, int l, int r) {
        if (l == r) {
            mx[o] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, o * 2, l, m);
        build(a, o * 2 + 1, m + 1, r);
        maintain(o);
    }

public:
    SegmentTree(const vector<int> &a) {
        size_t n = a.size();
        mx.resize(2 << bit_width(n - 1));
        build(a, 1, 0, n - 1);
    }

    // 找区间内的第一个 >= x 的数，并更新为 -1，返回这个数的下标（没有则返回 -1）
    int findFirstAndUpdate(int o, int l, int r, int x) {
        if (mx[o] < x) {
            // 区间没有 >= x 的数
            return -1;
        }
        if (l == r) {
            mx[o] = -1; // 更新为 -1，表示不能放水果
            return l;
        }
        int m = (l + r) / 2;
        int i = findFirstAndUpdate(o * 2, l, m, x); // 先递归左子树
        if (i < 0) {
            // 左子树没找到
            i = findFirstAndUpdate(o * 2 + 1, m + 1, r, x); // 再递归右子树
        }
        maintain(o);
        return i;
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets) {
        SegmentTree t(baskets);
        int n = baskets.size(), ans = 0;
        for (int x: fruits) {
            if (t.findFirstAndUpdate(1, 0, n - 1, x) < 0) {
                ans++;
            }
        }
        return ans;
    }
};
