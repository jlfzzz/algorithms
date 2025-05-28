//
// Created by 123 on 25-5-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int largestPathValue(string colors, vector<vector<int>>& edges) {
		int n = colors.size();
		vector<vector<int>> graph(n, vector<int>());
		vector<int> deg(n, 0);
		for (auto& edge : edges) {
			graph[edge[0]].push_back(edge[1]);
			deg[edge[1]]++;
		}

		int added = 0;
		queue<int> q;
		vector<vector<int>> memo(n, vector<int>(26));
		int ans = 1;
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				q.push(i);
				added++;
			}
		}

		while (!q.empty()) {
			int fa = q.front();
			q.pop();
			memo[fa][colors[fa] - 'a']++;
			for (int child : graph[fa]) {
				// 修正：应该传递父节点中各种颜色的最大计数
				for (int c = 0; c < 26; c++) {
					memo[child][c] = max(memo[child][c], memo[fa][c]);
				}
				deg[child]--;
				if (deg[child] == 0) {
					q.push(child);
					added++;
				}
			}
			ans = max(ans, memo[fa][colors[fa] - 'a']);
		}
		return added < n ? -1 : ans;
	}
};

class Solution2 {
public:
	int largestPathValue(string colors, vector<vector<int>>& edges) {
		int n = colors.size();
		vector<vector<int>> graph(n, vector<int>());
		for (auto& v : edges) {
			graph[v[0]].push_back(v[1]);
		}
		vector<int> visited(n, 0);
		vector<vector<int>> memo(n, vector<int>());
		bool have_ring = false;
		int ans = 0;
		auto dfs = [&](this auto&&dfs, int curr) -> vector<int>& {
			if (visited[curr] == 1) {
				have_ring = true;
				return memo[curr];
			}
			if (!memo[curr].empty() || visited[curr] == 2 || have_ring) {
				return memo[curr];
			}

			visited[curr] = 1;
			int idx = colors[curr] - 'a';
			memo[curr] = vector<int>(26);
			auto& v = memo[curr];
			for (int child : graph[curr]) {
				auto& child_v = dfs(child);
				if (have_ring)
					return v;
				for (int i = 0; i < 26; i++) {
					v[i] = max(v[i], child_v[i]);
				}
			}
			v[idx]++;
			ans = max(ans, v[idx]);
			visited[curr] = 2;
			return v;
		};
		for (int i = 0; i < n; i++) {
			dfs(i);
		}
		return have_ring ? -1 : ans;
	}
};

// dfs and 拓扑
class Solution3 {
public:
	int largestPathValue(string colors, vector<vector<int> > &edges) {
		int n = colors.size();
		vector<vector<int> > graph(n, vector<int>());
		for (auto &edge: edges) {
			graph[edge[0]].push_back(edge[1]);
		}

		// 判断有向环（DFS三色标记法）
		vector<int> color(n, 0); // 0:未访问, 1:递归栈, 2:已访问
		bool have_ring = false;
		auto dfs1 = [&](auto &&dfs1, int fa) -> void {
			if (color[fa] == 1) {
				have_ring = true;
				return;
			}
			if (color[fa] == 2 || have_ring) {
				return;
			}
			color[fa] = 1;
			for (int neighbour: graph[fa]) {
				dfs1(dfs1, neighbour);
			}
			color[fa] = 2;
		};
		for (int i = 0; i < n; i++) {
			if (color[i] == 0)
				dfs1(dfs1, i);
		}
		if (have_ring) {
			return -1;
		}

		vector<vector<int> > memo(n, vector<int>(26));
		vector<int> visited2(n);

		auto dfs = [&](auto &&dfs, int fa) -> vector<int> & {
			if (visited2[fa]) {
				return memo[fa];
			}

			visited2[fa] = true;
			auto &curr = memo[fa];
			for (int child: graph[fa]) {
				auto &temp = dfs(dfs, child);
				for (int i = 0; i < 26; i++) {
					curr[i] = max(curr[i], temp[i]);
				}
			}
			curr[colors[fa] - 'a']++;
			return curr;
		};

		int ans = 0;
		for (int i = 0; i < n; i++) {
			auto &v = dfs(dfs, i);
			for (int j = 0; j < 26; j++) {
				ans = max(ans, v[j]);
			}
		}
		return ans;
	}
};

class Solution2 {
public:
	int largestPathValue(string colors, vector<vector<int> > &edges) {
		int n = colors.size();
		vector<vector<int> > graph(n, vector<int>());
		vector<int> deg(n);
		for (auto &edge: edges) {
			int v0 = edge[0], v1 = edge[1];
			if (v0 == v1) {
				return -1;
			}
			graph[v0].push_back(v1);
			deg[v1]++;
		}

		vector<int> q;
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				q.emplace_back(i);
			}
		}

		vector<vector<int> > memo(n, vector<int>(26));
		int ans = 0;
		for (int i = 0; i < q.size(); i++) {
			int node = q[i];
			char curr = colors[node];
			memo[node][curr - 'a']++;
			ans = max(ans, memo[node][curr - 'a']);
			for (int neighbour: graph[node]) {
				for (int j = 0; j < 26; j++) {
					memo[neighbour][j] = max(memo[neighbour][j], memo[node][j]);
				}
				if (--deg[neighbour] == 0) {
					q.emplace_back(neighbour);
				}
			}
		}
		return q.size() == n ? ans : -1;
	}
};
