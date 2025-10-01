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
};

// 求1到i的max
template<class T>
class FenwickTreeMax {
    std::vector<T> tree;
    int size;
    const T IDENTITY = std::numeric_limits<T>::min();

public:
    // 构造函数，树状数组大小为 n（下标 1~n）
    FenwickTreeMax(int n) : tree(n + 1, IDENTITY), size(n) {}

    // 更新 a[i] = max(a[i], val)
    void update(int i, T val) {
        for (; i <= size; i += i & -i) {
            tree[i] = std::max(tree[i], val);
        }
    }

    // 查询 max(a[1] ... a[i])
    T query(int i) const {
        T res = IDENTITY;
        for (; i > 0; i &= i - 1) {
            res = std::max(res, tree[i]);
        }
        return res;
    }
};
