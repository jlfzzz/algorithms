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
#include <set>
#include <random>

using namespace std;

class Solution {
public:
    int maxValueOfCoins(vector<vector<int>> &piles, int k) {
        int n = piles.size();
        vector<vector<int>> prefix_sum(n, vector<int>());

        for (int i = 0; i < n; i++) {
            int m = piles[i].size();
            prefix_sum[i] = vector<int>(m + 1, 0);
            for (int j = 1; j <= m; j++) {
                prefix_sum[i][j] = prefix_sum[i][j - 1] + piles[i][j - 1];
            }
        }

        vector<int> dp(k + 1, -1);
        dp[0] = 0;
        int chosen = 0;
        for (int i = 0; i < n; i++) {
            int m = piles[i].size();
            chosen += m;
            int max_j = min(chosen, k);
            for (int j = max_j; j > 0; j--) {
                for (int l = 1; l <= m; l++) {
                    if (j - l >= 0 && dp[j - l] != -1) {
                        dp[j] = max(dp[j], dp[j - l] + prefix_sum[i][l]);
                    }
                }
            }
        }
        return dp[k];
    }
};