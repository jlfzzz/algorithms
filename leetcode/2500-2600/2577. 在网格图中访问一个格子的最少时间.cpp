//
// Created by 123 on 25-5-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minimumTime(vector<vector<int> > &grid) {
		int n = grid.size();
		int m = grid[0].size();
		if (grid[0][1] > 1 && grid[1][0] > 1)
			return -1;
		vector<vector<int>> dis(n, vector<int>(m, INT_MAX));
		priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
		pq.emplace(0, 0, 0);
		while (!pq.empty()) {
			auto [d, x, y] = pq.top();
			pq.pop();
			if (x == n - 1 && y == m - 1) {
				return d;
			}
			if (d > dis[x][y]) {
				continue;
			}

			for (auto& dir : DIR) {
				int new_x = x + dir[0];
				int new_y = y + dir[1];
				if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m) {
					int new_d = max(d + 1, grid[new_x][new_y]);
					new_d += (new_d - new_x - new_y) % 2;
					if (new_d < dis[new_x][new_y]) {
						dis[new_x][new_y] = new_d;
						pq.emplace(new_d, new_x, new_y);
					}
				}
			}
		}
	}
};

class Solution {
public:
	int minimumTime(vector<vector<int> > &grid) {
		int n = grid.size();
		int m = grid[0].size();
		if (grid[0][1] > 1 && grid[1][0] > 1) // 无法「等待」
			return -1;

		vector dis(n, vector<int>(m, INT_MAX / 2));
		dis[0][0] = 0;
		priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<> > pq;
		pq.emplace(0, 0, 0);
		while (true) {
			auto [curr_dis, x, y] = pq.top();
			pq.pop();
			if (curr_dis > dis[x][y]) {
				continue;
			}
			if (x == n - 1 && y == m - 1) {
				return curr_dis;
			}
			for (auto &dir: DIR) {
				int new_x = x + dir[0];
				int new_y = y + dir[1];
				if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m) {
					int new_dis = max(curr_dis + 1, grid[new_x][new_y]);
					new_dis += (new_dis - new_x - new_y) % 2;
					if (new_dis < dis[new_x][new_y]) {
						dis[new_x][new_y] = new_dis;
						pq.emplace(new_dis, new_x, new_y);
					}
				}
			}
		}
	}
};

class Solution {
	static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
	int minimumTime(vector<vector<int> > &grid) {
		int m = grid.size(), n = grid[0].size();
		if (grid[0][1] > 1 && grid[1][0] > 1) // 无法「等待」
			return -1;

		int vis[m][n];
		memset(vis, -1, sizeof(vis));
		auto check = [&](int end_time) -> bool {
			vis[m - 1][n - 1] = end_time;
			vector<pair<int, int> > q = {{m - 1, n - 1}};
			for (int t = end_time - 1; !q.empty(); --t) {
				vector<pair<int, int> > nxt;
				for (auto &[i, j]: q) {
					for (auto &d: dirs) {
						// 枚举周围四个格子
						int x = i + d[0], y = j + d[1];
						if (0 <= x && x < m && 0 <= y && y < n && vis[x][y] != end_time && grid[x][y] <= t) {
							if (x == 0 && y == 0) return true;
							vis[x][y] = end_time; // 用二分的值来标记，避免重复创建 vis 数组
							nxt.emplace_back(x, y);
						}
					}
				}
				q = move(nxt);
			}
			return false;
		};

		int left = max(grid.back().back(), m + n - 2) - 1, right = 1e5 + m + n; // 开区间
		while (left + 1 < right) {
			int mid = left + (right - left) / 2;
			(check(mid) ? right : left) = mid;
		}
		return right + (right + m + n) % 2;
	}
};
