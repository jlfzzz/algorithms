#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int maximumBeauty(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> diff(100002, 0);
    for (int x : nums) {
      diff[max(x - k, 0)]++;
      diff[min(x + k), 100001]--;
    }

    int ans = 0;
    for (int x : diff) {
      ans = max(ans, x);
    }
    return ans;
  }
};
