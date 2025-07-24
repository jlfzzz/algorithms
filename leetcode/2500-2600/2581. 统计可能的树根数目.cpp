#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	int rootCount(vector<vector<int> > &edges, vector<vector<int> > &guesses, int k) {
		int n = edges.size() + 1;
		vector<vector<int> > graph(n, vector<int>());

		for (auto &e: edges) {
			graph[e[0]].emplace_back(e[1]);
			graph[e[1]].emplace_back(e[0]);
		}

		vector<int> true_cnt(n, 0);

		// 改成用 long long 存猜测 (parent << 32) | child
		unordered_set<long long> guess_set;
		for (auto &g: guesses) {
			guess_set.insert(((long long) g[0] << 32) | g[1]);
		}

		auto dfs1 = [&](this auto &&dfs1, int i, int fa) -> int {
			int res = 0;
			for (int v: graph[i]) {
				if (v == fa) {
					continue;
				}
				res += dfs1(v, i) + (guess_set.count(((long long) i << 32) | v));
			}
			true_cnt[i] = res;
			return res;
		};

		int ans = 0;

		dfs1(0, -1);

		auto dfs2 = [&](this auto &&dfs2, int i, int fa) -> void {
			if (true_cnt[i] >= k) {
				ans++;
			}

			for (int v: graph[i]) {
				if (v == fa) {
					continue;
				}

				true_cnt[v] = true_cnt[i];
				if (guess_set.contains(((long long) i << 32) | v)) {
					true_cnt[v] -= 1;
				}
				if (guess_set.contains(((long long) v << 32) | i)) {
					true_cnt[v] += 1;
				}
				dfs2(v, i);
			}
		};

		dfs2(0, -1);
		return ans;
	}
};
