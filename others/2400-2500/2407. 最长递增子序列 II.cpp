//
// Created by 123 on 25-6-12.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int lengthOfLIS(vector<int> &nums, int k) {
		int m = ranges::max(nums);
		vector<int> mx(4 * m);

		auto update = [&](this auto&&update, int o, int l, int r, int target, int val)-> void {
			if (l == r) {
				mx[o] = val;
				return;
			}

			int mid = (l + r) / 2;
			if (target <= mid) {
				update(o * 2, l, mid, target, val);
			} else {
				update(o * 2 + 1, mid + 1, r, target, val);
			}
			mx[o] = max(mx[o * 2], mx[o * 2 + 1]);
		};

		auto query_mx = [&](this auto&&query_mx,int o, int l, int r, int L, int R) -> int {
			if (L <= l && r <= R) return mx[o];

			int mid = (l + r) / 2;
			int res = 0;
			if (L <= mid) {
				res = max(res, query_mx(o * 2, l, mid, L, R));
			}
			if (R > mid) {
				res = max(res, query_mx(o * 2 + 1, mid + 1, r, L, R));
			}
			return res;
		};

		for (int x: nums) {
			if (x == 1) {
				update(1, 1, m, 1, 1);
			} else {
				int t = 1 + query_mx(1, 1, m, max(x - k, 1), x - 1);
				update(1, 1, m, x, t);
			}
		}
		return mx[1];
	}
};


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
	int lengthOfLIS(vector<int> &nums, int k) {
		int mx = ranges::max(nums);
		SegmentTree st(mx);
		int ans = 0;
		for (int x : nums) {
			int temp = st.rangeMax(max(0, x - k), x - 1);
			st.update(x, temp + 1);
			ans = max(ans, temp + 1);
		}
		return ans;
	}
};



class Solution {
public:
	int lengthOfLIS(vector<int> &nums, int k) {
		int n = nums.size();
		int m = ranges::max(nums);
		SegmentTree st(m + 1);
		int ans = 0;

		for (int i = 0; i < n; i++) {
			int x = nums[i];
			auto mx = st.rangeMax(max(0, x - k), x - 1);
			ans = max((long long)ans, mx + 1);
			st.update(x, mx + 1);
		}
		return ans;
	}
};