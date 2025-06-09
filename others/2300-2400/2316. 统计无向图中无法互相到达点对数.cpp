//
// Created by 123 on 25-6-6.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class UnionFind {
public:
	vector<int> parent;
	vector<int> rank;
	int count;

	UnionFind(int n) {
		parent.resize(n);
		rank.resize(n);
		count = n;
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void unite(int x, int y) {
		int root_x = find(x);
		int root_y = find(y);

		if (root_x == root_y) {
			return;
		}

		if (rank[root_x] == rank[root_y]) {
			parent[root_x] = root_y;
			++rank[root_y];
		} else if (rank[root_x] > rank[root_y]) {
			parent[root_y] = root_x;
		} else {
			parent[root_x] = root_y;
		}

		--count;  // 修正：连通分量数量减少
	}
};

class Solution {
public:
	long long countPairs(int n, vector<vector<int>>& edges) {
		UnionFind uf(n);
		int m = edges.size();

		// 合并所有边连接的节点
		for (int i = 0; i < m; i++) {
			uf.unite(edges[i][0], edges[i][1]);
		}

		// 统计每个连通分量的大小
		unordered_map<int, int> componentSize;
		for (int i = 0; i < n; i++) {
			int root = uf.find(i);
			componentSize[root]++;
		}

		// 计算不连通的对数
		long long totalPairs = (long long)n * (n - 1) / 2;
		long long connectedPairs = 0;

		// 计算每个连通分量内部的连通对数
		for (auto &size: componentSize | views::values) {
			connectedPairs += (long long)size * (size - 1) / 2;
		}

		return totalPairs - connectedPairs;
	}
};