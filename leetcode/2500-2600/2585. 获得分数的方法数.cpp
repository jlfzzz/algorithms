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
    int waysToReachTarget(int target, vector<vector<int>> &types) {
        int MOD = 1e9 + 7;
        int n = types.size();
        vector<long long> dp(target + 1);
        dp[0] = 1;
        int sum = 0;

        for (int i = 0; i < n; i++) {
            int mark = types[i][1];
            int count = types[i][0];
            sum += mark * count;
            int max_j = min(target, sum);

            for (int j = mark; j <= max_j; j++) {
                dp[j] = (dp[j - mark] + dp[j]) % MOD;
            }

            for (int j = max_j; j >= (count + 1) * mark; j--) {
                dp[j] = (dp[j] - dp[j - (count + 1) * mark] + MOD) % MOD;
            }
        }

        return dp[target] % MOD;
    }
};

class Solution {
public:
    int waysToReachTarget(int target, vector<vector<int>> &types) {
        int MOD = 1e9 + 7;
        int n = types.size();
        vector<long long> dp(target + 1);
        dp[0] = 1;

        for (int i = 0; i < n; i++) {
            int mark = types[i][1];
            int count = types[i][0];
            vector<long long> temp(target + 1, 0);
            for (int j = 0; j <= count; j++) {
                for (int k = 0; k <= target; k++) {
                    if (k + j * mark <= target) {
                        temp[k + j * mark] = (temp[k + j * mark] + dp[k]) % MOD;
                    }
                }

            }
            swap(temp, dp);
        }

        return dp[target] % MOD;
    }
};