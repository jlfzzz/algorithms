//
// Created by 123 on 25-6-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 求前缀和，1到i
template<typename T>
class FenwickTree {
	vector<T> tree;

public:
	// 使用下标 1 到 n
	FenwickTree(int n) : tree(n + 1) {}

	// a[i] 增加 val
	// 1 <= i <= n
	void update(int i, T val) {
		for (; i < tree.size(); i += i & -i) {
			tree[i] += val;
		}
	}

	// 求前缀和 a[1] + ... + a[i]
	// 1 <= i <= n
	T pre(int i) const {
		T res = 0;
		for (; i > 0; i &= i - 1) {
			res += tree[i];
		}
		return res;
	}
};

// 求1到i的max
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



class NumArray {
private:
	vector<int> tree;
	vector<int> &nums;

	int lowBit(int x) {
		return x & -x;
	}

	void add(int index, int val) {
		while (index < tree.size()) {
			tree[index] += val;
			index += lowBit(index);
		}
	}

	int prefixSum(int index) {
		int sum = 0;
		while (index > 0) {
			sum += tree[index];
			index -= lowBit(index);
		}
		return sum;
	}

public:
	NumArray(vector<int>& nums) : tree(nums.size() + 1), nums(nums) {
		for (int i = 0; i < nums.size(); i++) {
			add(i + 1, nums[i]);
		}
	}

	void update(int index, int val) {
		add(index + 1, val - nums[index]);
		nums[index] = val;
	}

	int sumRange(int left, int right) {
		return prefixSum(right + 1) - prefixSum(left);
	}
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */