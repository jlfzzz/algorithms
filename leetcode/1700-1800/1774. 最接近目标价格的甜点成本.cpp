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

// 回溯//背包

class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int n = baseCosts.size();
        int m = toppingCosts.size();
        int ans = 123456789;
        

        auto dfs = [&](this auto&&dfs, int index, int curr_sum) -> void {
            if (index == m) {
                if (abs(curr_sum - target) < abs(ans - target)) {
                    ans = curr_sum;
                } else if (abs(curr_sum - target) == abs(ans - target)) {
                    ans = min(curr_sum, ans);
                }
                return;
            }

            int curr_topping = toppingCosts[index];
            dfs(index + 1, curr_sum);
            dfs(index + 1, curr_sum + curr_topping);
            dfs(index + 1, curr_sum + curr_topping + curr_topping);
        };


        for (int i = 0; i < n; i++) {
            int base_cost = baseCosts[i];
            dfs(0, base_cost);
        }

        return ans;

    }
};

class Solution {
public:
    int closestCost(vector<int> &baseCosts, vector<int> &toppingCosts, int target) {
        vector<bool> can(20001);
        for (int base : baseCosts)
            can[base] = true;
        toppingCosts.insert(toppingCosts.end(), toppingCosts.begin(), toppingCosts.end());
        for (int topping : toppingCosts) {
            for (int i = 20000; i >= topping; --i)
                can[i] = can[i] || can[i - topping];
        }
        int min_gap = INT_MAX, ans = 0;
        for (int i = 1; i <= 20000; ++i)
            if (can[i] && abs(i - target) < min_gap) {
                ans = i;
                min_gap = abs(i - target);
            }
        return ans;
    }
};