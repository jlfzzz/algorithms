//
// Created by 123 on 25-5-31.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int swimInWater(vector<vector<int> > &grid) {
		int n = grid.size();
		priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<> > pq;
		vector<vector<int> > times(n, vector<int>(n, INT_MAX / 2));
		times[0][0] = grid[0][0];
		pq.emplace(times[0][0], 0, 0);
		while (!pq.empty()) {
			auto [t, x, y] = pq.top();
			pq.pop();

			if (x == n - 1 && y == n - 1) {
				return t;
			}

			for (auto &dir: DIR) {
				int new_x = x + dir[0];
				int new_y = y + dir[1];
				if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n) {
					int min_t = max(grid[new_x][new_y], t);
					if (min_t < times[new_x][new_y]) {
						times[new_x][new_y] = min_t;
						pq.emplace(min_t, new_x, new_y);
					}
				}
			}
		}
		return -1;
	}
};

class Solution {
public:
	int swimInWater(vector<vector<int>>& grid) {
		int n = grid.size();
		int lo = grid[0][0];
		int hi = n * n;
		vector<vector<int>> visited(n, vector<int>(n, hi + hi));

		auto check = [&](int start_t) -> bool {
			queue<pair<int, int>> q;
			q.emplace(0, 0);
			visited[0][0] = start_t;
			while (!q.empty()) {
				auto [x, y] = q.front();
				q.pop();
				if (x == n - 1 && y == n - 1) {
					return true;
				}

				for (auto& dir : DIR) {
					int new_x = x + dir[0];
					int new_y = y + dir[1];
					if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n) {
						if (visited[new_x][new_y] != start_t && grid[new_x][new_y] <= start_t) {
							visited[new_x][new_y] = start_t;
							q.emplace(new_x, new_y);
						}
					}
				}
			}

			return visited[n - 1][n - 1] == start_t;
		};

		int ans = hi;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (check(mid)) {
				ans = mid;
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		return ans;
	}
};

class Solution {
public:
	int find(vector<int>& f, int x) {
		if (f[x] == x) {
			return x;
		}
		int fa = find(f, f[x]);
		f[x] = fa;
		return fa;
	}

	void merge(vector<int>& f, int x, int y) {
		int fx = find(f, x), fy = find(f, y);
		f[fx] = fy;
	}

	int swimInWater(vector<vector<int>>& grid) {
		int n = grid.size();
		vector<int> f(n * n);
		for (int i = 0; i < n * n; i++) {
			f[i] = i;
		}

		vector<pair<int, int>> idx(n * n); // 存储每个平台高度对应的位置
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				idx[grid[i][j]] = make_pair(i, j);
			}
		}

		vector<pair<int, int>> directions{{0,1},{0,-1},{1,0},{-1,0}};
		for (int threshold = 0; threshold < n * n; threshold++) {
			auto [i, j] = idx[threshold];
			for (const auto [di, dj]: directions) {
				int ni = i + di, nj = j + dj;
				if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] <= threshold) {
					merge(f, i * n + j, ni * n + nj);
				}
			}
			if (find(f, 0) == find(f, n * n - 1)) {
				return threshold;
			}
		}
		return -1; // cannot happen
	}
};