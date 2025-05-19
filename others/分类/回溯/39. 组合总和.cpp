#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> ans;
        vector<int> path;
        int sum;

        auto dfs = [&](this auto &&dfs, int index, int sum) {
            if (sum > target) return;

            if (sum == target) {
                ans.emplace_back(path);
                return;
            }

            if (index == candidates.size()) {
                if (sum == target) {
                    ans.emplace_back(path);
                }
                return;
            }

            dfs(index + 1, sum); //跳过

            int count = 0;

            while (sum < target) {
                path.emplace_back(candidates[index]);
                sum += candidates[index];
                dfs(index + 1, sum);
                count++;
            }

            while (count > 0) {
                path.pop_back();
                //sum -= candidates[index];
                count--;
            }
            };
        dfs(0, 0);
        return ans;
    }
};