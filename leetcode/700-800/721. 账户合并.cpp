#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
        unordered_map<string, vector<int>> email_to_idx;
        for (int i = 0; i < accounts.size(); i++) {
            for (int k = 1; k < accounts[i].size(); k++) {
                email_to_idx[accounts[i][k]].push_back(i);
            }
        }

        unordered_set<string> email_set; // 用于收集 DFS 中访问到的邮箱地址
        vector<int> vis(accounts.size());
        auto dfs = [&](auto &&dfs, int i) -> void {
            vis[i] = true;
            for (int k = 1; k < accounts[i].size(); k++) { // 遍历 i 的所有邮箱地址
                string &email = accounts[i][k];
                if (email_set.contains(email)) {
                    continue;
                }
                email_set.insert(email);
                for (int j : email_to_idx[email]) { // 遍历所有包含该邮箱地址的账户下标 j
                    if (!vis[j]) { // j 没有访问过
                        dfs(dfs, j);
                    }
                }
            }
            };

        vector<vector<string>> ans;
        for (int i = 0; i < vis.size(); i++) {
            if (vis[i]) {
                continue;
            }
            email_set.clear();
            dfs(dfs, i);

            vector<string> res = { accounts[i][0] };
            res.insert(res.end(), email_set.begin(), email_set.end());
            sort(res.begin() + 1, res.end());

            ans.push_back(res);
        }
        return ans;
    }
};