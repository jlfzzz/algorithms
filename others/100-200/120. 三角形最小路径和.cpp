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
#include <queue>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>> &triangle) {
        int n = triangle.size();

        vector<vector<int>> dp(n + 1, vector<int>(triangle[n - 1].size() + 1, INT_MAX));
        dp[1][1] = triangle[0][0];

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= triangle[i - 1].size(); j++) {
                if (i == 1 && j == 1) continue;

                dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j]) + triangle[i - 1][j - 1];
            }
        }

        int ans = INT_MAX;
        for (int i = 1; i <= triangle[n - 1].size(); i++) {
            ans = min(ans, dp[n][i]);
        }
        return ans;
    }
};