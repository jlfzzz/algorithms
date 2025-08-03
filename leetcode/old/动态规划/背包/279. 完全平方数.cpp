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
    int numSquares(int n) {
        if (n == 1) return 1;
        vector<vector<int>> dp(101, vector<int>(n + 1, 100000));

        // 一维代表选数字n，二维是count
        dp[0][0] = 0;
        for (int i = 1; i <= 100;i++) {
            dp[i][0] = 0;

            for (int j = 0; j <= n; j++) {
                dp[i][j] = dp[i - 1][j];

                if (i * i <= j) {
                    dp[i][j] = min(dp[i][j], dp[i][j - i * i] + 1);
                }
            }
        }

        int ans = 100000;
        for (auto &v : dp) {
            ans = min(v[n], ans);
        }
        return ans;
    }
};