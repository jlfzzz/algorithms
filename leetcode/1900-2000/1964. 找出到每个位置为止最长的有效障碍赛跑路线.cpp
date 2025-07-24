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
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<int> ans;
        vector<int> dp;
        for (int i = 0; i < n; i++) {
            auto it = ranges::upper_bound(dp, obstacles[i]);
            if (it == dp.end()) {
                dp.push_back(obstacles[i]);
                ans.push_back(dp.size());
            } else {
                *it = obstacles[i];
                ans.push_back(it - dp.begin() + 1);
            }
        }
        return ans;
    }
};



// 方法2超时了

class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int> &obstacles) {
        vector<int> ans;
        int n = obstacles.size();
        vector<int> dp(n, 1);
        ans.emplace_back(dp[0]);
        for (int i = 1; i < n; i++) {
            // dp[i] = dp[i - 1];
            for (int j = 0; j < i; j++) {
                if (obstacles[j] <= obstacles[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans.emplace_back(dp[i]);
        }
        return ans;
    }
};