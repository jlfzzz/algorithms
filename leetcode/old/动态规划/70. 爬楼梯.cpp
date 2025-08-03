#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        vector<int> f(n + 1);
        f[0] = f[1] = 1;
        for (int i = 2; i <= n; i++) {
            f[i] = f[i - 1] + f[i - 2];
        }
        return f[n];
    }
};

class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n, -1);
        dp[0] = 1;
        auto dfs = [&](this auto &&dfs, int height) -> int {
            if (height < 0) return 1;

            if (dp[height] != -1) return dp[height];

            dp[height] = dfs(height - 1) + dfs(height - 2);
            return dp[height];
            };
        return dfs(n - 1);
    }
};