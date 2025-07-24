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

using namespace std;

// 1 我的偏方二分答案   2 正常 反着算 dp

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>> &dungeon) {
        int n = dungeon.size();
        int m = dungeon[0].size();
        int ans = 500000, mx = 500000;
        int mn = 1;

        if (dungeon[0][0] < 0) mn = -dungeon[0][0] + 1;

        while (mn < mx) {
            int mid = mn + (mx - mn) / 2;
            vector<vector<int>> dp(n + 1, vector<int>(m + 1, -500000));
            dp[1][1] = mid + dungeon[0][0];

            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    if (i == 1 && j == 1) continue;

                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + dungeon[i - 1][j - 1];
                    if (dp[i][j] <= 0) dp[i][j] = -500000;
                }
            }

            int finalHealth = dp[n][m];
            if (finalHealth < 1) {
                mn = mid + 1;
            } else {
                ans = min(ans, mid);
                mx = mid;
            }
        }

        return ans;
    }
};

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>> &dungeon) {
        int n = dungeon.size();
        int m = dungeon[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 500'000));

        dp[n][m - 1] = dp[n - 1][m] = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int minn = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(minn - dungeon[i][j], 1);
            }
        }

        return dp[0][0];
    }
};