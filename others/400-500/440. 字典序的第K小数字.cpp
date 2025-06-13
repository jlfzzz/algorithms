//
// Created by 123 on 25-6-9.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int findKthNumber(int n, int k) {
		auto helper = [&](int node) -> int {
			int size = 0;
			long long left = node, right = node + 1;
			while (left <= n) {
				size += min(right, n + 1LL) - left;
				left *= 10; // 继续，计算下一层
				right *= 10;
			}
			return size;
		};

		k--;
		int node = 1;
		while (k > 0) {
			int size = helper(node);
			if (size <= k) {
				k -= size;
				node++;
			} else {
				node *= 10;
				k--;
			}
		}
		return node;
 	}
};



class Solution {
public:
	int findKthNumber(int n, int k) {
		// 逐层统计 node 子树大小
		auto count_subtree_size = [&](int node) -> int {
			// 子树大小不会超过 n，所以 size 用 int 类型
			// 但计算过程中的 left 和 right 会超过 int，所以用 long long 类型
			int size = 0;
			long long left = node, right = node + 1;
			while (left <= n) {
				// 这一层的最小值是 left，最大值是 min(right, n + 1) - 1
				size += min(right, n + 1LL) - left;
				left *= 10; // 继续，计算下一层
				right *= 10;
			}
			return size;
		};

		int node = 1;
		k--; // 访问节点 node
		while (k > 0) {
			int size = count_subtree_size(node);
			if (size <= k) { // 向右，跳过 node 子树
				node++; // 访问 node 右侧兄弟节点
				k -= size; // 访问子树中的每个节点，以及新的 node 节点
			} else { // 向下，深入 node 子树
				node *= 10; // 访问 node 的第一个儿子
				k--; // 访问新的 node 节点
			}
		}
		return node;
	}
};