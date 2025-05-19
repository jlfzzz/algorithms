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
#include <cstring>
#include <array> 

using namespace std;

class Solution {
public:
    int maxCollectedFruits(vector<vector<int>> &fruits) {
        int n = fruits.size();
        vector<vector<int>> dp(n, vector<int>(n, -10000000));
        dp[0][0] = fruits[0][0];

        for (int i = 1; i < n; i++) {
            dp[i][i] = dp[i - 1][i - 1] + fruits[i][i];
        }

        dp[n - 1][0] = fruits[n - 1][0];
        dp[0][n - 1] = fruits[0][n - 1];
        for (int i = 1; i < n - 1; i++) {
            for (int j = n - 1; j > i; j--) {
                int left = -10000000, leftDown = -10000000, leftUp = -10000000;
                if (j + 1 < n) {
                    leftDown = dp[j + 1][i - 1];
                }

                left = dp[j][i - 1];
                leftUp = dp[j - 1][i - 1];
                dp[j][i] = max({ left, leftDown, leftUp }) + fruits[j][i]; // 左下角的

                int upRight = -10000000, up = -10000000, upLeft = -10000000;
                if (j + 1 < n) {
                    upRight = dp[i - 1][j + 1];
                }

                up = dp[i - 1][j];
                upLeft = dp[i - 1][j - 1];
                dp[i][j] = max({ up, upLeft, upRight }) + fruits[i][j];
            }
        }

        dp[n - 1][n - 1] += dp[n - 2][n - 1] + dp[n - 1][n - 2];
        return dp[n - 1][n - 1];
    }
};