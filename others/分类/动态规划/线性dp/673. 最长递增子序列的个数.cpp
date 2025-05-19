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
    int findNumberOfLIS(vector<int> &nums) {
        int n = nums.size();
        vector<pair<int, int>> dp(n, { 1,1 });
        int mxLen = 1;

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            for (int j = 0; j < i; j++) {

                if (nums[j] < nums[i]) {
                    int before = dp[j].first + 1;

                    if (before > dp[i].first) {
                        dp[i].first = before;
                        dp[i].second = dp[j].second;
                    } else if (before == dp[i].first) {
                        dp[i].second += dp[j].second;
                    }

                    mxLen = max(mxLen, dp[i].first);
                }

            }

        }

        int ans = 0;
        for (auto &p : dp) {
            if (p.first == mxLen) {
                ans += p.second;
            }
        }
        return ans;
    }
};