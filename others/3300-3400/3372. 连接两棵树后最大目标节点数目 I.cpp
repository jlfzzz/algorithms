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
	vector<int> maxTargetNodes(vector<vector<int> > &edges1, vector<vector<int> > &edges2, int k) {
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

		auto bfs = [&](int root, vector<vector<int> > &curr_graph, int size, int max_k) -> int {
			if (max_k < 0) {
				return 0;
			}
			queue<int> q;
			int ans = 1;
			q.push(root);
			vector<int> visited(size, 0);
			int dis = 0;
			visited[root] = 1;
			while (!q.empty() && dis < max_k) {
				int curr_n = q.size();
				for (int i = 0; i < curr_n; i++) {
					int fa = q.front();
					q.pop();
					for (int child: curr_graph[fa]) {
						if (!visited[child]) {
							visited[child] = 1;
							q.push(child);
							ans++;
						}
					}
				}
				dis++;
			}
			return ans;
		};

		int max_2 = 0;
		for (int i = 0; i < m; i++) {
			max_2 = max(bfs(i, graph2, m, k - 1), max_2);
		}

		vector<int> ans(n);
		// ans.push_back(max_2);
		// return ans;
		for (int i = 0; i < n; i++) {
			ans[i] = bfs(i, graph1, n, k) + max_2;
			//ans.push_back(bfs(i, graph1, n, k));
		}

		return ans;
	}
};
