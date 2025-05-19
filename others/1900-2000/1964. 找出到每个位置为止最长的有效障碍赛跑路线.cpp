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

// 方法2超时了
class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int> &obstacles) {
        int n = obstacles.size();
        vector<int> f;
        vector<int> ans;

        for (int i = 0; i < n; i++) {
            int x = obstacles[i];
            auto it = ranges::upper_bound(f, x);
            if (it == f.end()) {
                f.emplace_back(x);
                ans.emplace_back(f.size());
            } else {
                *it = x;
                ans.emplace_back(it - f.begin() + 1);
            }
        }
        return ans;

    }
};

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