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
    long long maximumTotalDamage(vector<int> &power) {
        unordered_map<int, int> cnt;
        for (int x : power) {
            cnt[x]++;
        }

        vector<pair<int, int>> a(cnt.begin(), cnt.end());
        ranges::sort(a);

        int n = a.size();
        vector<long long> f(n + 1);
        for (int i = 0, j = 0; i < n; i++) {
            auto &[x, c] = a[i];
            while (a[j].first < x - 2) {
                j++;
            }
            f[i + 1] = max(f[i], f[j] + (long long)x * c);
        }
        return f[n];
    }
};








// 内存超了

class Solution {
public:
    long long maximumTotalDamage(vector<int> &power) {
        if (power.empty()) return 0; // Handle empty input case

        // Find max element first
        auto max_it = ranges::max_element(power);
        int mx = *max_it;

        // Use long long for counts to prevent overflow if a number appears many times
        unordered_map<long long, long long> record; // key: power, value: count
        for (int p : power) { // Use different loop variable than original 'i'
            record[p]++;
        }

        // dp array needs to store long long values
        vector<long long> dp(mx + 1, 0LL); // Initialize with 0LL (long long zero)
        // dp[0] = 0; // Already initialized to 0LL

        // Calculate dp[1] if mx >= 1
        if (mx >= 1) {
            // Score is count * power value. Accessing record[1] gives count.
            // Multiply by 1LL to ensure long long calculation.
            dp[1] = record[1] * 1LL; // max(record[1] * 1LL, dp[0]) simplifies to this
        }
        // Early return if max element is 1
        if (mx == 1) return dp[1];

        // Calculate dp[2] if mx >= 2
        if (mx >= 2) {
            // Correct logic: max of (not taking 2 -> dp[1]) and (taking 2 -> record[2] * 2LL)
            dp[2] = max(dp[1], record[2] * 2LL);
        }
        // Early return if max element is 2
        if (mx == 2) return dp[2];


        // Correct DP transition for i >= 3
        for (int i = 3; i <= mx; i++) { // Original loop variable 'i'
            // Calculate score for taking power i, ensuring long long multiplication
            long long current_score = record[i] * (long long)i;

            // Option 1: Don't take power i. Max damage is dp[i-1].
            long long dont_choose = dp[i - 1];

            // Option 2: Take power i. Max damage is current_score + dp[i-3].
            // dp[i-3] handles the constraint of not taking i-1 and i-2.
            long long choose = current_score + dp[i - 3]; // i is guaranteed >= 3 here

            // Correct state transition: compare choosing vs not choosing power i
            dp[i] = max(dont_choose, choose);
            // *** The original logic 'max({ dp[i - 1], dp[i - 2], dp[i - 3] + current_score })' was incorrect ***
        }
        return dp[mx];
    }
};