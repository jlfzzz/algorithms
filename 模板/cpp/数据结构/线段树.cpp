#include <algorithm>

#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 线段树节点结构，维护 sum/max/min，并支持懒惰标记 lazy
struct SegmentTreeNode {
	long long sum;
	long long maxVal;
	long long minVal;
	long long lazy;

	SegmentTreeNode(long long s = 0, long long mx = LLONG_MIN, long long mn = LLONG_MAX, long long lz = 0)
		: sum(s), maxVal(mx), minVal(mn), lazy(lz) {
	}
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
	void build(long long val, int node, int l, int r) {
		// 参数改为 long long
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
	void update(int node, int l, int r, int idx, long long val) {
		// 参数改为 long long
		if (l == r) {
			tree[node] = SegmentTreeNode(val, val, val, 0); // 显式清理 lazy
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
	void rangeAdd(int node, int l, int r, int ql, int qr, long long val) {
		// 参数改为 long long
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
	long long queryMin(int node, int l, int r, int ql, int qr) {
		// 返回类型改为 long long
		if (qr < l || r < ql) return LLONG_MAX;
		if (ql <= l && r <= qr) return tree[node].minVal;
		pushDown(node, l, r);
		int mid = (l + r) / 2;
		return min(queryMin(2 * node, l, mid, ql, qr),
			queryMin(2 * node + 1, mid + 1, r, ql, qr));
	}

	// 查找第一个 max >= target 的位置
	int find_first_helper(int node, int l, int r, int ql, int qr, long long target) {
		// 参数改为 long long
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
	SegmentTree(int _n, long long val = 0) {
		// 参数改为 long long
		n = _n;
		tree.resize(4 * n);
		build(val, 1, 0, n - 1);
	}

	// 单点赋值
	void update(int idx, long long val) {
		// 参数改为 long long
		update(1, 0, n - 1, idx, val);
	}

	// 区间求和
	long long rangeSum(int l, int r) {
		return query(1, 0, n - 1, l, r).sum;
	}

	// 区间最大值
	long long rangeMax(int l, int r) {
		// 返回类型改为 long long
		return query(1, 0, n - 1, l, r).maxVal;
	}

	// 区间最小值
	long long rangeMin(int l, int r) {
		// 返回类型改为 long long
		return queryMin(1, 0, n - 1, l, r);
	}

	// 区间加 val
	void rangeAdd(int l, int r, long long val) {
		// 参数改为 long long
		rangeAdd(1, 0, n - 1, l, r, val);
	}

	// 获取单点值（最大、最小、sum 都一样）
	long long getValue(int idx) {
		// 返回类型改为 long long
		return query(1, 0, n - 1, idx, idx).maxVal;
	}

	// 查找第一个 max >= target 的位置
	int find_first(int L, int R, long long target) {
		// 参数改为 long long，增强边界检查
		if (L < 0 || L >= n || L >= R) return -1;
		R = min(R, n);
		return find_first_helper(1, 0, n - 1, L, R - 1, target);
	}
};

// 无注释版本
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
	// 都是闭区间的query [l, r]
	SegmentTree(const vector<int> &nums) {
		n = nums.size();
		tree.resize(4 * n);
		build(nums, 1, 0, n - 1);
	}

	SegmentTree(int _n, ll val = 0) {
		n = _n + 1;
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
