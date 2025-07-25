#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
    public:
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges) {
        int n = nums.size();
        vector<vector<int>> g(n, vector<int>());
        for (auto &e: edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> xors(n);

        auto dfs1 = [&](this auto &&dfs1, int i, int fa) -> int {
            int res = nums[i];
            for (int v: g[i]) {
                if (v == fa) {
                    continue;
                }

                res ^= dfs1(v, i);
            }
            xors[i] = res;
            return res;
        };
                
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            dfs1(i, -1);

            
        }
        return ans;
    }
};



class Solution {
    public:
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges) {
        int n = nums.size();
        vector<vector<int>> g(n, vector<int>());
        for (auto &e: edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> in(n);
        vector<int> out(n);
        int time = 0;
        vector<int> xors(n);

        auto dfs1 = [&](this auto &&dfs1, int i, int fa) -> int {
            int res = nums[i];
            in[i] = time++;
            for (int v: g[i]) {
                if (v == fa) {
                    continue;
                }

                res ^= dfs1(v, i);
            }
            xors[i] = res;
            out[i] = time;
            return res;
        };

        auto is_ancestor = [&](int x, int y) -> bool { return in[x] > in[y] and out[x] <= out[y]; };

        dfs1(0, -1);
        int ans = INT_MAX;
        int root = xors[0];
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int a, b, c;
                if (is_ancestor(i, j)) {
                    a = xors[i], b = xors[j] ^ xors[i], c = root ^ xors[j];
                } else if (is_ancestor(j, i)) {
                    a = xors[j], b = xors[i] ^ xors[j], c = root ^ xors[i];
                } else {
                    a = xors[i], b = xors[j], c = root ^ xors[i] ^ xors[j];
                }
                // if (ans == 6) {
                //     cout << i << endl << j << endl;
                // }
                ans = min(ans, max({a, b, c}) - min({a, b, c}));
            }
        }
        return ans;
    }
};
