#include <bits/stdc++.h>

using namespace std;

class Solution {
    public:
    int rootCount(vector<vector<int>> &edges, vector<vector<int>> &guesses, int k) {
        int n = edges.size() + 1;
        vector<vector<int>> graph(n, vector<int>());

        for (auto &e: edges) {
            graph[e[0]].emplace_back(e[1]);
            graph[e[1]].emplace_back(e[0]);
        }

        vector<int> true_cnt(n, 0);

        unordered_map<int, int> child_to_fa;
        for (auto &g: guesses) {
            child_to_fa[g[1]] = g[0];
        }

        auto dfs1 = [&](this auto &&dfs1, int i, int fa) -> int {
            int res = 0;
            for (int v: graph[i]) {
                if (v == fa) {
                    continue;
                }
                res += dfs1(v, i) + (child_to_fa[v] == i);
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
                if (child_to_fa[v] == i) {
                    true_cnt[v] -= 1;
                }
                dfs2(v, i);
            }
        };
        dfs2(0, -1);
        return ans;
    }
};
