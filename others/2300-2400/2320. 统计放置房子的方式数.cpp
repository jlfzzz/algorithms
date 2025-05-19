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
    int countHousePlacements(int n) {
        vector<vector<long long>> dp(n, vector<long long>(2, 0)); // dp[i][0] choose
        // dp[i][1] skip 

        int mod = 1000000007;
        dp[0][0] = 1;
        dp[0][1] = 1;

        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][1] % mod;
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
        }
        long long ans = (((dp[n - 1][0] + dp[n - 1][1]) % mod) * ((dp[n - 1][0] + dp[n - 1][1]) % mod)) % mod;

        return ans;
    }
};

class Solution {
public:
    int countHousePlacements(int n) {
        long long prev_placed = 1;  // Corresponds to dp[0][0]
        long long prev_skipped = 1; // Corresponds to dp[0][1]
        long long current_placed = 0;
        long long current_skipped = 0;
        int mod = 1000000007;

        if (n == 1)
            return 4; // Handle n=1 separately or adjust loop

        for (int i = 1; i < n; ++i) {
            current_placed = prev_skipped;
            current_skipped = (prev_placed + prev_skipped) % mod;

            prev_placed = current_placed;
            prev_skipped = current_skipped;
        }
        long long total_one_side = (current_placed + current_skipped) % mod;
        long long ans = (total_one_side * total_one_side) % mod;
        return (int)ans;
    }
};