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
	int makeConnected(int n, vector<vector<int>>& connections) {
		// 如果边的数量不足 n - 1 条，根本无法连通所有节点
		if (connections.size() < n - 1)
			return -1;

		// 建图
		vector<vector<int>> graph(n);
		for (const auto& conn : connections) {
			graph[conn[0]].push_back(conn[1]);
			graph[conn[1]].push_back(conn[0]);
		}

		// 用于标记每个节点是否访问过
		vector<bool> visited(n, false);
		// 用于防止重复计边的集合（无向边只处理一次）
		set<pair<int, int>> usedEdges;
		int extra = 0;

		// DFS 函数，带边检查
		auto dfs = [&](auto&& dfs, int curr) -> void {
			for (int next : graph[curr]) {
				auto edge = minmax(curr, next);  // 统一无向边方向
				if (usedEdges.count(edge)) continue;
				usedEdges.insert(edge);

				if (visited[next]) {
					// next 已访问 ⇒ 出现环 ⇒ 多余边
					extra++;
				} else {
					visited[next] = true;
					dfs(dfs, next);
				}
			}
		};

		// 主程序，统计连通块数量
		int parts = 0;
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				visited[i] = true;
				dfs(dfs, i);
				parts++;
			}
		}

		// 要连通所有块，需要至少 parts - 1 条边
		return extra >= parts - 1 ? parts - 1 : -1;
	}
};

class UnionFind {
public:
	vector<int> parent;
	vector<int> rank;
	int count;

	explicit UnionFind(const int n) : count(n) {
		parent.resize(n);
		rank.resize(n);
		ranges::fill(rank, 1);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	bool unite(int x, int y) {
		int root_x = find(x);
		int root_y = find(y);

		if (root_x == root_y) {
			return false;
		}

		if (rank[root_x] == rank[root_y]) {
			parent[root_x] = root_y;
			rank[root_y] += 1;
		} else if (rank[root_x] > rank[root_y]) {
			parent[root_y] = root_x;
		} else {
			parent[root_x] = root_y;
		}
		count--;
		return true;
	}
};

class Solution {
public:
	int makeConnected(int n, vector<vector<int>>& connections) {
		if (connections.size() < n - 1)
			return -1;

		UnionFind uf(n);
		int extra = 0;
		for (const auto& conn : connections) {
			if (!uf.unite(conn[0], conn[1])) {
				extra++;
			}
		}

		return extra >= uf.count - 1 ? uf.count - 1 : -1;
	}
};
