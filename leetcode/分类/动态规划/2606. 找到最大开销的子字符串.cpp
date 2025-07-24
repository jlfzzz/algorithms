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
    int maximumCostSubstring(string s, string chars, vector<int> &vals) {
        unordered_map<char, int> mp;
        for (int i = 0; i < chars.size(); i++) {
            mp[chars[i]] = vals[i];
        }

        int n = s.size();
        vector<int> dp(n);

        if (mp.find(s[0]) != mp.end()) {
            dp[0] = mp[s[0]];
        } else {
            dp[0] = s[0] - 'a' + 1;
        }
        int ans = dp[0];
        for (int i = 1; i < n; i++) {
            char c = s[i];
            int val;
            if (mp.find(c) != mp.end()) {
                val = mp[c];
            } else {
                val = c - 'a' + 1;
            }

            dp[i] = max(dp[i - 1] + val, val);
            ans = max(ans, dp[i]);
        }
        return ans > 0 ? ans : 0;
    }
};