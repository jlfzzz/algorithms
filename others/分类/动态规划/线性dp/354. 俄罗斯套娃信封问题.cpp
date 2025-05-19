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
#include <cstring>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>> &envelopes) {
        int n = envelopes.size();
        if (n == 0) return 0;

        // 按宽度升序排序，宽度相同时按高度降序排序
        sort(envelopes.begin(), envelopes.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
            });

        // 在高度上求最长递增子序列
        vector<int> dp;
        for (auto &env : envelopes) {
            int height = env[1];
            auto it = lower_bound(dp.begin(), dp.end(), height);
            if (it == dp.end()) {
                dp.push_back(height);
            } else {
                *it = height;
            }
        }

        return dp.size();
    }
};



// 超时了
class Solution {
public:
    int maxEnvelopes(vector<vector<int>> &envelopes) {
        int n = envelopes.size();
        vector<pair<int, int>> pairs(n);
        for (int i = 0; i < n; i++) {
            pairs[i].first = envelopes[i][0];
            pairs[i].second = envelopes[i][1];
        }

        ranges::sort(pairs);
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (pairs[j].first < pairs[i].first && pairs[j].second < pairs[i].second) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
                
        }
        return *ranges::max_element(dp);
    }
};