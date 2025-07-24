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

using namespace std;

class Solution {
public:
    int paintWalls(vector<int> &cost, vector<int> &time) {
        int n = cost.size();
        vector<int> dp(n + 1, 1e9);
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            vector<int> temp = dp;
            int curr_time = time[i - 1];
            int curr_cost = cost[i - 1];
            for (int j = 0; j <= n; j++) {
                int new_walls = min(n, j + curr_time + 1);
                int new_cost = dp[j] + curr_cost;
                temp[new_walls] = min(temp[new_walls], new_cost);
            }
            swap(temp, dp);
        }

        return dp[n];
    }
};