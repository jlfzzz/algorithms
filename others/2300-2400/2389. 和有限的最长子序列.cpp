#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>

using namespace std;

class Solution {
public:
    std::vector<int> answerQueries(std::vector<int> &nums, std::vector<int> &queries) {
        int n = nums.size();

        sort(nums.begin(), nums.end());
        vector<int> prefixSum(n, 0);
        prefixSum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        vector<int> ans;
        for (int x : queries) {
            auto it = ranges::lower_bound(prefixSum, x);

            if (it == prefixSum.end()) {
                ans.push_back(n); // 所有元素和都小于x
            } else if (*it == x) {
                ans.push_back(it - prefixSum.begin() + 1); // 恰好等于x
            } else {
                ans.push_back(it - prefixSum.begin()); // 大于x
            }
            
        }

        return ans;
    }
};