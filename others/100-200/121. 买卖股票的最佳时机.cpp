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
  int maxProfit(vector<int> &prices) {
    int n = prices.size();
    int ans = 0;
    int mn = prices[0];
    for (int i = 1; i < n; i++) {
      if (prices[i] < mn) {
        mn = prices[i];
      } else {
        ans = max(ans, prices[i] - mn);
      }
    }
    return ans;
  }
};

class Solution1 {
public:
  int maxProfit(vector<int> &prices) {
    int n = prices.size();
    int mn = prices[0];

    int ans = 0;
    for (int i = 1; i < n; i++) {
      if (prices[i] >= mn) {
        ans = max(ans, prices[i] - mn);
      } else {
        mn = prices[i];
      }
    }
    return ans;
  }
};


class Solution2 {
public:
  int maxProfit(vector<int> &prices) {
    int n = prices.size();
    vector<int> dp(n);

    dp[0] = prices[0];
    if (n == 0) return dp[0];

    int ans = 0;
    for (int i = 1; i < n; i++) {
      if (prices[i] >= dp[i - 1]) {
        ans = max(ans, prices[i] - dp[i - 1]);
      } else {
        dp[i] = prices[i];
      }
    }
    return ans;
  }
};