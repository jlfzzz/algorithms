//
// Created by 123 on 25-6-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
		vector<vector<int>> graph(n);
		for (auto& edge : edges) {
			graph[edge[0]].push_back(edge[1]);
			graph[edge[1]].push_back(edge[0]);
		}
		int ans = 0;

		auto dfs = [&](this auto&&dfs, int node, int parent) -> long long {
			vector<long long> childCosts;

			for (int v : graph[node]) {
				if (v != parent) {
					childCosts.push_back(dfs(v, node));
				}
			}

			if (childCosts.empty()) {
				return cost[node];
			}

			long long mx = *max_element(childCosts.begin(), childCosts.end());

			for (long long c : childCosts) {
				if (c < mx) {
					ans++;
				}
			}
			return cost[node] + mx;
		};

		dfs(0, -1);
		return ans;
	}
};