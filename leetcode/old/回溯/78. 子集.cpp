#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<int>> ans;
    vector<int> v;
    int n;

    vector<vector<int>> subsets(vector<int> &nums) {
        n = nums.size();

        dfs(0, nums);
        return ans;
    }

    void dfs(int index, vector<int> &nums) {
        if (index == n) {
            ans.emplace_back(v);
            return;
        }

        dfs(index + 1, nums);
        v.push_back(nums[index]);
        dfs(index + 1, nums);
        v.pop_back();
    }
};