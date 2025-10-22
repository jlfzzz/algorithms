//
// Created by 123 on 25-6-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 左闭右闭
    T rangeSum(int l, int r) const { return this->pre(r) - this->pre(l - 1); }

    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    T getVal(int i) { return rangeSum(i, i); }

    void setVal(int i, T val) {
        T delta = val - getVal(i);
        update(i, delta);
    }

    // 点更新取 max
    void updateMax(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            if (val > tree[i]) {
                tree[i] = val;
            }
        }
    }

    T preMax(int i) const {
        T res = numeric_limits<T>::min();
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }
};
