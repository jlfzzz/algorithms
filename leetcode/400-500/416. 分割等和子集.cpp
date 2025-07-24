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
    bool canPartition(vector<int> &nums) {
        int sum = 0;
        for (int x : nums) sum += x;
        if (sum % 2 == 1) return false;

        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;

        for (int x : nums) {
            for (int j = target; j >= x; j--) {
                dp[j] = dp[j] || dp[j - x];
            }
        }

        return dp[target];
    }
};


class Solution {
public:
    bool canPartition(vector<int> &nums) {
        int sum = 0;
        for (int x : nums) sum += x;

        if (sum % 2 == 1 || nums.size() < 2) return false;

        int target = sum / 2;
        int n = nums.size();
        // vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));
        // for (int i = 0; i <= n; i++) {
        //     dp[i][0] = 0;
        // }

        vector<vector<long long>> dp(n + 1, vector<long long>(target + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            dp[i][0] = 1;
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i - 1][j];

                if (nums[i - 1] <= j) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % 100000000;
                }
            }
        }
        return dp[n][target] != 0;
    }
};




class Solution {
public:
    bool canPartition(vector<int> &nums) {
        int sum = 0;
        for (int x : nums) sum += x;

        if (sum % 2 == 1 || nums.size() < 2) return false;

        int target = sum / 2;
        vector<int> dp(target + 1, -1);
        dp[0] = 0;
        for (int num : nums) {
            for (int i = target; i >= num; i--) {
                if (dp[i - num] != -1) {
                    dp[i] = dp[i - num] + 1;
                }
            }
        }
        return dp[target] != -1;
    }
};






class Solution {
public:
    bool canPartition(vector<int> &nums) {
        int n = nums.size();
        if (n < 2) {
            return false;
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());
        if (sum & 1) {
            return false;
        }
        int target = sum / 2;
        if (maxNum > target) {
            return false;
        }
        vector<vector<int>> dp(n, vector<int>(target + 1, 0));
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;
        for (int i = 1; i < n; i++) {
            int num = nums[i];
            for (int j = 1; j <= target; j++) {
                if (j >= num) {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][target];
    }
};
