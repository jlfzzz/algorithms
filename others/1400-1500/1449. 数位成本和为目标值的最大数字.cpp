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
#include <bitset>
#include <stack>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int> &cost, int target) {
        vector<int> dp(target + 1, INT_MIN);
        dp[0] = 0;
        for (int c : cost) {
            for (int j = c; j <= target; ++j) {
                dp[j] = max(dp[j], dp[j - c] + 1);
            }
        }
        if (dp[target] < 0) {
            return "0";
        }
        string ans;
        for (int i = 8, j = target; i >= 0; i--) {
            for (int c = cost[i]; j >= c && dp[j] == dp[j - c] + 1; j -= c) {
                ans += '1' + i;
            }
        }
        return ans;
    }
};

class Solution {
public:
    string largestNumber(vector<int> &cost, int target) {
        vector<string> dp(target + 1, "#");
        dp[0] = "";

        // 遍历成本
        for (int t = 0; t <= target; ++t) {
            if (dp[t] == "#") continue;

            // 遍历数字 9~1，尝试加在当前状态后面
            for (int d = 8; d >= 0; --d) {
                int c = cost[d];
                if (t + c <= target) {
                    string candidate = dp[t] + to_string(d + 1);
                    if (dp[t + c] == "#" || candidate.length() > dp[t + c].length() ||
                        (candidate.length() == dp[t + c].length() && candidate > dp[t + c])) {
                        dp[t + c] = candidate;
                    }
                }
            }
        }

        return dp[target] == "#" ? "0" : dp[target];
    }
};
