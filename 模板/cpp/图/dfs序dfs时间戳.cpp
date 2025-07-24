//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// lc 2322
// 根据dfs遍历的时间顺序，能判断一个节点和它的字节点的父子关系。
class Solution {
public:
	int minimumScore(vector<int> &nums, vector<vector<int> > &edges) {
		int n = nums.size();
		vector<vector<int> > g(n);
		for (auto &e: edges) {
			int x = e[0], y = e[1];
			g[x].push_back(y);
			g[y].push_back(x);
		}

		vector<int> xr(n), in(n), out(n);
		int clock = 0;
		auto dfs = [&](this auto &&dfs, int x, int fa) -> void {
			in[x] = ++clock; // 递
			xr[x] = nums[x];
			for (int y: g[x]) {
				if (y != fa) {
					dfs(y, x);
					xr[x] ^= xr[y];
				}
			}
			out[x] = clock; // 归
		};
		dfs(0, -1);

		// 判断 x 是否为 y 的祖先
		auto is_ancestor = [&](int x, int y) -> bool {
			return in[x] < in[y] && in[y] <= out[x];
		};

		int ans = INT_MAX;
		// 枚举：删除 x 与 x 父节点之间的边，删除 y 与 y 父节点之间的边
		for (int x = 2; x < n; x++) {
			for (int y = 1; y < x; y++) {
				int a, b, c;
				if (is_ancestor(x, y)) {
					// x 是 y 的祖先
					a = xr[y], b = xr[x] ^ a, c = xr[0] ^ xr[x];
				} else if (is_ancestor(y, x)) {
					// y 是 x 的祖先
					a = xr[x], b = xr[y] ^ a, c = xr[0] ^ xr[y];
				} else {
					// x 和 y 分别属于两棵不相交的子树
					a = xr[x], b = xr[y], c = xr[0] ^ a ^ b;
				}
				ans = min(ans, max({a, b, c}) - min({a, b, c}));
				if (ans == 0) {
					// 不可能变小
					return 0; // 提前返回
				}
			}
		}
		return ans;
	}
};
