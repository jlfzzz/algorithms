//
// Created by 123 on 25-6-12.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class BookMyShow {
public:
	int n, m;
	vector<int> mn;
	vector<long long> sum;

	void update(int o, int l, int r, int i, int val) {
		if (l == r) {
			mn[o] += val;
			sum[o] += val;
			return;
		}

		int m = (l + r) >> 1;
		if (i <= m) {
			update(o * 2, l, m, i, val);
		} else {
			update(o * 2 + 1, m + 1, r, i, val);
		}
		mn[o] = min(mn[o * 2], mn[o * 2 + 1]);
		sum[o] = sum[o * 2] + sum[o * 2 + 1];
	}

	long long query_sum(int o, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return sum[o];
		}
		long long res = 0;
		int m = (l + r) >> 1;
		if (L <= m) {
			res = query_sum(o * 2, l, m, L, R);
		}
		if (R > m) {
			res += query_sum(o * 2 + 1, m + 1, r, L, R);
		}
		return res;
	}

	int find_first(int o, int l, int r, int R, int val) {
		if (mn[o] > val) {
			return -1;
		}
		if (l == r) {
			return l;
		}
		int m = (l + r) >> 1;
		if (mn[o * 2] <= val) {
			return find_first(o * 2, l, m, R, val);
		}
		if (R > m) {
			return find_first(o * 2 + 1, m + 1, r, R, val);
		}
		return -1;
	}


	BookMyShow(int n, int m) : n(n), m(m), mn(4 << __lg(n)), sum(4 << __lg(n)) {
	}

	vector<int> gather(int k, int maxRow) {
		int r = find_first(1, 0, n - 1, maxRow, m - k);
		if (r < 0) {
			return {};
		}
		int c = query_sum(1, 0, n - 1, r, r);
		update(1, 0, n - 1, r, k);
		return {r, c};
	}

	bool scatter(int k, int maxRow) {
		long long s = query_sum(1, 0, n - 1, 0, maxRow);
		if (s > static_cast<long long>(m * (maxRow + 1) - k)) {
			return false;
		}
		int i = find_first(1, 0, n - 1, maxRow, m - 1);
		while (k) {
			int left = min(m - (int)query_sum(1, 0, n - 1, i, i), k);
			update(1, 0, n - 1, i, left);
			k -= left;
			i++;
		}
		return true;
	}
};


#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 线段树节点结构，维护 sum/max/min，并支持懒惰标记 lazy
struct SegmentTreeNode {
    long long sum;
    long long maxVal;  // 改为 long long 保持一致
    long long minVal;  // 改为 long long 保持一致
    long long lazy;

    SegmentTreeNode(long long s = 0, long long mx = LLONG_MIN, long long mn = LLONG_MAX, long long lz = 0)
        : sum(s), maxVal(mx), minVal(mn), lazy(lz) {}
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    // 合并两个子节点的信息
    SegmentTreeNode merge(const SegmentTreeNode &a, const SegmentTreeNode &b) {
        return SegmentTreeNode(
            a.sum + b.sum,
            max(a.maxVal, b.maxVal),
            min(a.minVal, b.minVal)
        );
    }

    // 将 lazy 值应用到当前节点
    void apply(int node, int l, int r, long long val) {
        tree[node].sum += val * (r - l + 1);
        tree[node].maxVal += val;
        tree[node].minVal += val;
        tree[node].lazy += val;
    }

    // 将懒惰标记下传到子节点
    void pushDown(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            int mid = (l + r) / 2;
            apply(2 * node, l, mid, tree[node].lazy);
            apply(2 * node + 1, mid + 1, r, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }

    // 构建线段树（从数组）
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

    // 构建线段树（所有值相同）
    void build(long long val, int node, int l, int r) {  // 参数改为 long long
        if (l == r) {
            tree[node] = SegmentTreeNode(val, val, val);
            return;
        }
        int mid = (l + r) / 2;
        build(val, 2 * node, l, mid);
        build(val, 2 * node + 1, mid + 1, r);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    // 单点更新
    void update(int node, int l, int r, int idx, long long val) {  // 参数改为 long long
        if (l == r) {
            tree[node] = SegmentTreeNode(val, val, val, 0);  // 显式清理 lazy
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

    // 区间查询（sum/max/min）
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

    // 区间加操作
    void rangeAdd(int node, int l, int r, int ql, int qr, long long val) {  // 参数改为 long long
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

    // 区间最小值查询
    long long queryMin(int node, int l, int r, int ql, int qr) {  // 返回类型改为 long long
        if (qr < l || r < ql) return LLONG_MAX;
        if (ql <= l && r <= qr) return tree[node].minVal;
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        return min(queryMin(2 * node, l, mid, ql, qr),
                   queryMin(2 * node + 1, mid + 1, r, ql, qr));
    }

    // 查找第一个 max >= target 的位置
    int find_first_helper(int node, int l, int r, int ql, int qr, long long target) {  // 参数改为 long long
        if (qr < l || r < ql || tree[node].maxVal < target) return -1;
        if (l == r) return l;
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        int left_result = find_first_helper(2 * node, l, mid, ql, qr, target);
        if (left_result != -1) return left_result;
        return find_first_helper(2 * node + 1, mid + 1, r, ql, qr, target);
    }

public:
    // 从数组构造
    SegmentTree(const vector<int> &nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    // 构造固定值
    SegmentTree(int _n, long long val = 0) {  // 参数改为 long long
        n = _n;
        tree.resize(4 * n);
        build(val, 1, 0, n - 1);
    }

    // 单点赋值
    void update(int idx, long long val) {  // 参数改为 long long
        update(1, 0, n - 1, idx, val);
    }

    // 区间求和
    long long rangeSum(int l, int r) {
        return query(1, 0, n - 1, l, r).sum;
    }

    // 区间最大值
    long long rangeMax(int l, int r) {  // 返回类型改为 long long
        return query(1, 0, n - 1, l, r).maxVal;
    }

    // 区间最小值
    long long rangeMin(int l, int r) {  // 返回类型改为 long long
        return queryMin(1, 0, n - 1, l, r);
    }

    // 区间加 val
    void rangeAdd(int l, int r, long long val) {  // 参数改为 long long
        rangeAdd(1, 0, n - 1, l, r, val);
    }

    // 获取单点值（最大、最小、sum 都一样）
    long long getValue(int idx) {  // 返回类型改为 long long
        return query(1, 0, n - 1, idx, idx).maxVal;
    }

    // 查找第一个 max >= target 的位置
    int find_first(int L, int R, long long target) {  // 参数改为 long long，增强边界检查
        if (L < 0 || L >= n || L >= R) return -1;
        R = min(R, n);
        return find_first_helper(1, 0, n - 1, L, R - 1, target);
    }
};

class BookMyShow {
private:
	SegmentTree st;
	int n, m;

public:
	BookMyShow(int n, int m) : n(n), m(m), st(n, m) {
	}

	vector<int> gather(int k, int maxRow) {
		// 检查参数有效性
		if (k <= 0 || k > m || maxRow < 0 || maxRow >= n) {
			return {};
		}

		// 找到第一个有足够连续空座位的排
		int row = st.find_first(0, maxRow + 1, k);
		if (row == -1) {
			return {};
		}

		// 获取当前排的空座位数
		int available = st.getValue(row);
		// 起始座位编号 = 总座位数 - 当前空座位数
		int startSeat = m - available;

		// 更新该排的空座位数
		st.update(row, available - k);

		return {row, startSeat};
	}

	bool scatter(int k, int maxRow) {
		// 检查参数有效性
		if (k <= 0 || maxRow < 0 || maxRow >= n) {
			return false;
		}

		// 检查前maxRow+1排的总空座位数是否足够
		long long totalAvailable = st.rangeSum(0, maxRow);
		if (totalAvailable < k) {
			return false;
		}

		// 从第0排开始，逐排分配座位
		for (int row = 0; row <= maxRow && k > 0; row++) {
			int available = st.getValue(row);
			if (available > 0) {
				int take = min(k, available);
				st.update(row, available - take);
				k -= take;
			}
		}

		return true;
	}
};