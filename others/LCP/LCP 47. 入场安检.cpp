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
    int securityCheck(vector<int> &capacities, int k) {
        int mod = 1e9 + 7;
        int n = capacities.size();
        vector<int> dp(k + 1, 0);
        dp[0] = 1; // Base case: 1 way to get a total delay of 0 (all FIFO)

        for (int i = 0; i < n; i++) { // Iterate through each room/item
            int delay_potential = capacities[i] - 1;

            // Capacity >= 1 is guaranteed by constraints, so delay_potential >=
            // 0. If delay_potential is 0 (capacity is 1), the DP update works
            // correctly: dp[j] = (dp[j] + dp[j-0]) % mod = (2 * dp[j]) % mod.
            // This correctly doubles the ways, representing the choice of FIFO
            // or LIFO for this room.

            // Iterate j from k down to delay_potential to avoid using the same
            // room multiple times in one outer step
            for (int j = k; j >= delay_potential; j--) {
                // dp[j] currently stores ways to get sum j using rooms 0 to
                // i-1. dp[j - delay_potential] stores ways to get sum
                // j-delay_potential using rooms 0 to i-1. By making room i
                // LIFO, the ways stored in dp[j - delay_potential] now
                // contribute to sum j.
                dp[j] = (dp[j] + dp[j - delay_potential]) % mod;
            }
        }

        return dp[k]; // The number of ways to get a total delay sum of exactly
        // k
    }
};