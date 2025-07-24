#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;//
// Created by 123 on 25-5-21.
//

class Solution {
public:
  int maxSum(vector<int>& nums) {
    int n = nums.size();
    int ans = -1;
    unordered_map<int, int> mp;
    for (int x : nums) {
      int temp = x, mx = 0;
      while (temp > 0) {
        mx = max(mx, temp % 10);
        temp /= 10;
      }
      if (mp.find(mx) == mp.end()) {
        mp[mx] = x;
      } else {
        ans = max(ans, x + mp[mx]);
        mp[mx] = max(mp[mx], x);
      }
    }
    return ans;
  }
};
