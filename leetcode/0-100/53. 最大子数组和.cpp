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
    int maxSubArray(vector<int> &nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = nums[0];
        int ans = nums[0];

        for (int i = 1; i < n; i++) {
            dp[i] = max(dp[i - 1], 0) + nums[i];
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};