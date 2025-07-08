#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <cstring>

using namespace std;

#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct SegmentTreeNode {
    ll sum, maxVal, minVal, lazy;
    SegmentTreeNode(ll s = 0, ll mx = LLONG_MIN, ll mn = LLONG_MAX, ll lz = 0)
        : sum(s), maxVal(mx), minVal(mn), lazy(lz) {
    }
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    SegmentTreeNode merge(const SegmentTreeNode &a, const SegmentTreeNode &b) {
        return SegmentTreeNode(
            a.sum + b.sum,
            max(a.maxVal, b.maxVal),
            min(a.minVal, b.minVal)
        );
    }

    void apply(int node, int l, int r, ll val) {
        tree[node].sum += val * (r - l + 1);
        tree[node].maxVal += val;
        tree[node].minVal += val;
        tree[node].lazy += val;
    }

    void pushDown(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            int mid = (l + r) / 2;
            apply(2 * node, l, mid, tree[node].lazy);
            apply(2 * node + 1, mid + 1, r, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }

    void build(const vector<int> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = SegmentTreeNode(nums[l], nums[l], nums[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(nums, 2 * node, l, mid);
        build(nums, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void build(ll val, int node, int l, int r) {
        if (l == r) {
            tree[node] = SegmentTreeNode(val, val, val);
            return;
        }
        int mid = (l + r) / 2;
        build(val, 2 * node, l, mid);
        build(val, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node] = SegmentTreeNode(val, val, val, 0);
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(2 * node, l, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, r, idx, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    SegmentTreeNode query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return SegmentTreeNode(0, LLONG_MIN, LLONG_MAX);
        if (ql <= l && r <= qr)
            return tree[node];
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        auto left = query(2 * node, l, mid, ql, qr);
        auto right = query(2 * node + 1, mid + 1, r, ql, qr);
        return merge(left, right);
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        rangeAdd(2 * node, l, mid, ql, qr, val);
        rangeAdd(2 * node + 1, mid + 1, r, ql, qr, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    ll queryMin(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return LLONG_MAX;
        if (ql <= l && r <= qr) return tree[node].minVal;
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        return min(queryMin(2 * node, l, mid, ql, qr),
            queryMin(2 * node + 1, mid + 1, r, ql, qr));
    }

    int find_first_helper(int node, int l, int r, int ql, int qr, ll target) {
        if (qr < l || r < ql || tree[node].maxVal < target) return -1;
        if (l == r) return l;
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        int left_result = find_first_helper(2 * node, l, mid, ql, qr, target);
        if (left_result != -1) return left_result;
        return find_first_helper(2 * node + 1, mid + 1, r, ql, qr, target);
    }

public:
    SegmentTree(const vector<int> &nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    SegmentTree(int _n, ll val = 0) {
        n = _n;
        tree.resize(4 * n);
        build(val, 1, 0, n - 1);
    }

    void update(int idx, ll val) {
        update(1, 0, n - 1, idx, val);
    }

    ll rangeSum(int l, int r) {
        return query(1, 0, n - 1, l, r).sum;
    }

    ll rangeMax(int l, int r) {
        return query(1, 0, n - 1, l, r).maxVal;
    }

    ll rangeMin(int l, int r) {
        return queryMin(1, 0, n - 1, l, r);
    }

    void rangeAdd(int l, int r, ll val) {
        rangeAdd(1, 0, n - 1, l, r, val);
    }

    ll getValue(int idx) {
        return query(1, 0, n - 1, idx, idx).sum;
    }

    int find_first(int L, int R, ll target) {
        if (L < 0 || R > n || L >= R) return -1;
        return find_first_helper(1, 0, n - 1, L, R - 1, target);
    }
};

class Solution {
public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        int n = scores.size();
        SegmentTree st(ranges::max(ages) + 1);
        int ans = 0;
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = { scores[i], ages[i] };
        }

        ranges::sort(v);
        for (int i = 0; i < n; i++) {
            int age = v[i].second;
            int score = v[i].first;
            int temp = st.rangeMax(0, age);
            int currentBest = temp + score;
            st.update(age, currentBest);
            ans = max(ans, currentBest);
        }
        return ans;
    }
};


class Solution {
public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        int n = ages.size();
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = { ages[i], scores[i] };
        }

        ranges::sort(v);
        vector<int> dp(n);
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (v[j].second <= v[i].second) {
                    dp[i] = max(dp[i], dp[j] + v[i].second);
                }
            }
        }
        return ranges::max(dp);
    }
};

class Solution {
public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        int n = scores.size();
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            v[i].second = scores[i];
            v[i].first = ages[i];
        }
        ranges::sort(v);
        vector<int> dp(n);
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (v[j].second <= v[i].second) {
                    dp[i] = max(dp[j], dp[i]);
                }
            }
            dp[i] += v[i].second;
        }
        return ranges::max(dp);
    }
};


class Solution {
public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        int n = scores.size();
        pair<int, int> a[n];
        for (int i = 0; i < n; ++i)
            a[i] = { scores[i], ages[i] };
        sort(a, a + n);

        int f[n]; memset(f, 0, sizeof(f));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j)
                if (a[j].second <= a[i].second)
                    f[i] = max(f[i], f[j]);
            f[i] += a[i].first;
        }
        return *max_element(f, f + n);
    }
};


template <class T>
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

class Solution {
public:
    int bestTeamScore(vector<int> &scores, vector<int> &ages) {
        int n = scores.size();
        FenwickTreeMax<int> ft(ranges::max(ages) + 1);
        int ans = 0;
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = { scores[i], ages[i] };
        }

        ranges::sort(v);
        for (int i = 0; i < n; i++) {
            int age = v[i].second;
            int score = v[i].first;
            int temp = ft.query(age);
            int currentBest = temp + score;
            ft.update(age, currentBest);
            ans = max(ans, currentBest);
        }
        return ans;
    }
};
