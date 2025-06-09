//
// Created by 123 on 25-5-28.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	vector<int> maxTargetNodes(vector<vector<int> > &edges1, vector<vector<int> > &edges2) {
		int n = edges1.size() + 1;
		int m = edges2.size() + 1;
		vector<vector<int> > graph1(n, vector<int>());
		vector<vector<int> > graph2(m, vector<int>());
		for (auto &edge: edges1) {
			graph1[edge[0]].push_back(edge[1]);
			graph1[edge[1]].push_back(edge[0]);
		}
		for (auto &edge: edges2) {
			graph2[edge[0]].push_back(edge[1]);
			graph2[edge[1]].push_back(edge[0]);
		}

		auto bfs = [&](const vector<vector<int> > &g) -> int {
			queue<int> q;
			int dis = 0;
			q.push(0);
			int count = 0;
			vector<bool> visited(g.size(), false);
			while (!q.empty()) {
				int curr_n = q.size();
				for (int j = 0; j < curr_n; j++) {
					if (dis % 2 == 0) {
						count++;
					}
					int fa = q.front();
					q.pop();
					visited[fa] = true;
					for (int neighbour : g[fa]) {
						if (neighbour != fa && !visited[neighbour]) {
							q.push(neighbour);
						}
					}
				}
				dis++;
			}
			return count;
		};

		int even2 = m - bfs(graph2);
		int g2 = max(m - even2, even2);
		int even1 = bfs(graph1);
		vector<int> ans(n);
		int dis = 0;
		queue<int> q;
		q.push(0);
		vector<bool> visited(n, false);
		while (!q.empty()) {
			int curr_n = q.size();
			for (int j = 0; j < curr_n; j++) {
				int fa = q.front();
				q.pop();
				visited[fa] = true;
				if (dis % 2 == 0) {
					ans[fa] = even1 + g2;
				} else {
					ans[fa] = n - even1 + g2;
				}
				for (int neighbour : graph1[fa]) {
					if (neighbour != fa && !visited[neighbour]) {
						q.push(neighbour);
					}
				}
			}
			dis++;
		}
		return ans;
	}
};

class Solution {
public:
	vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
		auto count = [](vector<vector<int>>& edges) {
			vector<vector<int>> g(edges.size() + 1);
			for (auto& e : edges) {
				int x = e[0], y = e[1];
				g[x].push_back(y);
				g[y].push_back(x);
			}

			array<int, 2> cnt{};
			auto dfs = [&](this auto&& dfs, int x, int fa, int d) -> void {
				cnt[d]++;
				for (int y : g[x]) {
					if (y != fa) {
						dfs(y, x, d ^ 1);
					}
				}
			};
			dfs(0, -1, 0);
			return pair(g, cnt);
		};

		auto [_, cnt2] = count(edges2);
		int max2 = max(cnt2[0], cnt2[1]);

		auto [g, cnt1] = count(edges1);
		vector<int> ans(g.size(), max2);
		auto dfs = [&](this auto&& dfs, int x, int fa, int d) -> void {
			ans[x] += cnt1[d];
			for (int y : g[x]) {
				if (y != fa) {
					dfs(y, x, d ^ 1);
				}
			}
		};
		dfs(0, -1, 0);
		return ans;
	}
};
