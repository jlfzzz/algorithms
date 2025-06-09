//
// Created by 123 on 25-5-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
		vector<vector<int>> ans;
		auto dfs = [&](this auto&& dfs, int child, vector<int>& path) -> void {
			if (child == graph.size() - 1) {
				ans.emplace_back(path);
				return;
			}

			for (int son : graph[child]) {
				path.emplace_back(son);
				dfs(son, path);
				path.pop_back();
			}
		};
		vector<int> path;
		path.emplace_back(0);
		dfs(0, path);
		return ans;
	}
};