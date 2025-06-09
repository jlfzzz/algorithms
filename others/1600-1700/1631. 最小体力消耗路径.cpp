//
// Created by 123 on 25-6-3.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 并查集模板
class UnionFind {
public:
	vector<int> parent;
	vector<int> size;
	int n;
	// 当前连通分量数目
	int setCount;

public:
	UnionFind(int _n): n(_n), setCount(_n), parent(_n), size(_n, 1) {
		iota(parent.begin(), parent.end(), 0);
	}

	int findset(int x) {
		return parent[x] == x ? x : parent[x] = findset(parent[x]);
	}

	bool unite(int x, int y) {
		x = findset(x);
		y = findset(y);
		if (x == y) {
			return false;
		}
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
		--setCount;
		return true;
	}

	bool connected(int x, int y) {
		x = findset(x);
		y = findset(y);
		return x == y;
	}
};

class Solution {
public:
	int minimumEffortPath(vector<vector<int>>& heights) {
		int m = heights.size();
		int n = heights[0].size();
		vector<tuple<int, int, int>> edges;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				int id = i * n + j;
				if (i > 0) {
					edges.emplace_back(id - n, id, abs(heights[i][j] - heights[i - 1][j]));
				}
				if (j > 0) {
					edges.emplace_back(id - 1, id, abs(heights[i][j] - heights[i][j - 1]));
				}
			}
		}
		ranges::sort(edges, [](const auto& e1, const auto& e2) {
			auto&& [x1, y1, v1] = e1;
			auto&& [x2, y2, v2] = e2;
			return v1 < v2;
		});

		UnionFind uf(m * n);
		int ans = 0;
		for (const auto [x, y, v]: edges) {
			uf.unite(x, y);
			if (uf.connected(0, m * n - 1)) {
				ans = v;
				break;
			}
		}
		return ans;
	}
};

class Solution {
public:
	int minimumEffortPath(vector<vector<int>>& heights) {
		int row = heights.size();
		int col = heights[0].size();
		vector<vector<int>> visited(row, vector<int>(col, INT_MAX / 2));
		priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
					   greater<>>
			pq;
		pq.emplace(0, 0, 0);
		while (!pq.empty()) {
			auto [cost, x, y] = pq.top();
			pq.pop();

			if (x == row - 1 && y == col - 1) {
				return cost;
			}
			int curr = heights[x][y];
			for (auto& dir : DIR) {
				int newX = x + dir[0];
				int newY = y + dir[1];

				if (newX >= 0 && newY >= 0 && newX < row && newY < col) {
					int newCost = max(abs(heights[newX][newY] - curr), cost);
					if (newCost < visited[newX][newY]) {
						pq.emplace(newCost, newX, newY);
						visited[newX][newY] = newCost;
					}
				}
			}
		}
		return 1;
	}
};
