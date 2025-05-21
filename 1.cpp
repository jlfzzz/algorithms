#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int maximumSum(vector<int>& nums) {
    vector<int> v(100, 0);
    int ans = 0;
    for (int i = 0; i < nums.size(); i++) {
      int x = nums[i];
      int sum = 0;
      while (x > 0) {
        sum += x % 10;
        x /= 10;
      }
      ans = max(ans, x + v[sum]);
      v[sum] = max(v[sum], x);
    }
    return ans;
  }
};
