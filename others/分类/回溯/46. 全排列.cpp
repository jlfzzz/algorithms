#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> ans;
        vector<int> selected;
        int n = nums.size();

        auto dfs = [&](this auto &&dfs, int idx) {
            if (idx == n) {
                ans.emplace_back(selected);
                return;
            }

            for (int i = 0; i < n; i++) {
                if (ranges::find(selected, nums[i]) != selected.end()) continue;
                selected.emplace_back(nums[i]);
                dfs(idx + 1);
                selected.pop_back();
            }
            };
        dfs(0);
        return ans;
    }
};