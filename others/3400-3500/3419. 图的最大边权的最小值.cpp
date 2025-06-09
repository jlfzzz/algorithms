//
// Created by 123 on 25-6-7.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minMaxWeight(int n, vector<vector<int> > &edges, int threshold) {
		int m = edges.size();
		if (m < n - 1) {
			return -1;
		}

		vector<vector<pair<int, int> > > g(n);
		for (auto &e: edges) {
			int x = e[0], y = e[1], w = e[2];
			g[y].emplace_back(x, w);
		}

		vector<int> dis(n, INT_MAX);
		dis[0] = 0;
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
		pq.emplace(0, 0); // (路径最大边权, 节点编号)
		while (!pq.empty()) {
			auto [x, d] = pq.top();
			pq.pop();

			if (d > dis[x]) {
				continue;
			}

			for (auto &[y, w]: g[x]) {
				int new_d = max(d, w);
				if (new_d < dis[y]) {
					dis[y] = new_d;
					pq.emplace(y, new_d);
				}
			}
		}

		int ans = ranges::max(dis);
		return ans == INT_MAX ? -1 : ans;
	}
};


class Solution {
public:
	int minMaxWeight(int n, vector<vector<int> > &edges, int threshold) {
		int m = edges.size();
		int hi = 0;
		vector<vector<pair<int, int> > > graph(n, vector<pair<int, int> >());
		for (auto &edge: edges) {
			graph[edge[1]].emplace_back(edge[0], edge[2]);
			hi = max(hi, edge[2]);
		}

		vector<int> visited(n, hi + 1);
		auto check = [&](int limit) -> bool {
			int left = n;
			auto dfs = [&](this auto &&dfs, int x) -> void {
				left--;
				visited[x] = limit;
				for (auto [y, weight]: graph[x]) {
					if (visited[y] != limit && weight <= limit) {
						visited[y] = limit;
						dfs(y);
					}
				}
			};
			dfs(0);
			return left == 0;
		};

		int lo = 1;
		++hi;
		int ans = 1e9;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (check(mid)) {
				hi = mid;
				ans = mid;
			} else {
				lo = mid + 1;
			}
		}

		return ans == 1e9 ? -1 : ans;
	}
};


class Solution {
public:
	int minMaxWeight(int n, vector<vector<int> > &edges, int) {
		if (edges.size() < n - 1) {
			return -1;
		}

		vector<vector<pair<int, int> > > g(n);
		int max_w = 0;
		for (auto &e: edges) {
			int x = e[0], y = e[1], w = e[2];
			g[y].emplace_back(x, w);
			max_w = max(max_w, w);
		}

		vector<int> vis(n);
		auto check = [&](int upper) -> bool {
			int left = n;
			auto dfs = [&](this auto &&dfs, int x) -> void {
				vis[x] = upper; // 避免每次二分重新创建 vis 数组
				left--;
				for (auto &[y, w]: g[x]) {
					if (w <= upper && vis[y] != upper) {
						dfs(y);
					}
				}
			};
			dfs(0);
			return left == 0;
		};

		int left = 0, right = max_w + 1;
		while (left + 1 < right) {
			int mid = left + (right - left) / 2;
			(check(mid) ? right : left) = mid;
		}
		return right > max_w ? -1 : right;
	}
};

class Solution {
public:
	int minMaxWeight(int n, vector<vector<int> > &edges, int threshold) {
		int m = edges.size();
		if (m < n - 1) {
			return -1;
		}

		vector<vector<pair<int, int> > > g(n);
		for (auto &e: edges) {
			int x = e[0], y = e[1], w = e[2];
			g[y].emplace_back(x, w);
		}

		vector<int> dis(n, INT_MAX);
		dis[0] = 0;
		priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
		pq.emplace(0, 0); // (路径最大边权, 节点编号)
		while (!pq.empty()) {
			auto [x, d] = pq.top();
			pq.pop();

			if (d > dis[x]) {
				continue;
			}

			for (auto &[y, w]: g[x]) {
				int new_d = max(d, w);
				if (new_d < dis[y]) {
					dis[y] = new_d;
					pq.emplace(y, new_d);
				}
			}
		}

		int ans = ranges::max(dis);
		return ans == INT_MAX ? -1 : ans;
	}
};
