//
// Created by 123 on 25-6-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

template<typename T>
class BIT {
    vector<T> tree;

public:
    BIT(int n) : tree(n + 1) {}

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

template<typename T>
class FenwickTree2D {
    vector<vector<T>> tree;
    int n, m;

public:
    FenwickTree2D(int n, int m) : n(n), m(m), tree(n + 1, vector<T>(m + 1)) {}

    void update(int x, int y, T val) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                tree[i][j] += val;
            }
        }
    }

    // 查询左上角 (1, 1) 到 右下角 (x, y) 的矩阵和
    T pre(int x, int y) const {
        T res = 0;
        for (int i = x; i > 0; i &= i - 1) {
            for (int j = y; j > 0; j &= j - 1) {
                res += tree[i][j];
            }
        }
        return res;
    }

    // 查询子矩阵和: 左上 (x1, y1) 到 右下 (x2, y2)
    T rangeSum(int x1, int y1, int x2, int y2) const {
        return pre(x2, y2) - pre(x1 - 1, y2) - pre(x2, y1 - 1) + pre(x1 - 1, y1 - 1);
    }

    T getVal(int x, int y) { return rangeSum(x, y, x, y); }

    void setVal(int x, int y, T val) {
        T delta = val - getVal(x, y);
        update(x, y, delta);
    }

    void updateMax(int x, int y, T val) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                if (val > tree[i][j]) {
                    tree[i][j] = val;
                }
            }
        }
    }

    T preMax(int x, int y) const {
        T res = numeric_limits<T>::min();
        for (int i = x; i > 0; i &= i - 1) {
            for (int j = y; j > 0; j &= j - 1) {
                res = max(res, tree[i][j]);
            }
        }
        return res;
    }
};

// 二维，矩阵区间加
template<typename T>
class FenwickTree2DRange {
    int n, m;
    vector<vector<T>> t[4];

    void _add(int x, int y, T val) {
        for (int i = x; i <= n; i += i & -i) {
            for (int j = y; j <= m; j += j & -j) {
                t[0][i][j] += val;
                t[1][i][j] += val * x;
                t[2][i][j] += val * y;
                t[3][i][j] += val * x * y;
            }
        }
    }

    T _ask(int x, int y) const {
        T res[4] = {0};
        for (int i = x; i > 0; i &= i - 1) {
            for (int j = y; j > 0; j &= j - 1) {
                res[0] += t[0][i][j];
                res[1] += t[1][i][j];
                res[2] += t[2][i][j];
                res[3] += t[3][i][j];
            }
        }
        return (T) (x + 1) * (y + 1) * res[0] - (T) (y + 1) * res[1] - (T) (x + 1) * res[2] + res[3];
    }

public:
    FenwickTree2DRange(int n, int m) : n(n), m(m) {
        for (auto &k: t) {
            k.assign(n + 1, vector<T>(m + 1, 0));
        }
    }

    void rangeUpdate(int x1, int y1, int x2, int y2, T val) {
        _add(x1, y1, val);
        _add(x1, y2 + 1, -val);
        _add(x2 + 1, y1, -val);
        _add(x2 + 1, y2 + 1, val);
    }

    T rangeQuery(int x1, int y1, int x2, int y2) const {
        return _ask(x2, y2) - _ask(x1 - 1, y2) - _ask(x2, y1 - 1) + _ask(x1 - 1, y1 - 1);
    }
};
