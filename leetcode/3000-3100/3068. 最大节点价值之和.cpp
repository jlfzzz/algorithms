//
// Created by 32098 on 25-5-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
      ll f0 = 0, f1 = LLONG_MIN / 2;
      int n = nums.size();
      for (int i = 0; i < n; i++) {
        ll temp = max(f0 + (nums[i] ^ k), f1 + nums[i]);
        f0 = max(f0 + nums[i], f1 + (nums[i] ^ k));
        f1 = temp;
      }
      return f0;
    }
};

class Solution2 {
public:
  long long maximumValueSum(vector<int> &nums, int k, vector<vector<int>> &edges) {
    int n = nums.size();
    vector<vector<int>> g(n);
    for (auto &e : edges) {
      int x = e[0], y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }

    function<pair<long long, long long>(int, int)> dfs = [&](int x, int fa) -> pair<long long, long long> {
      long long f0 = 0, f1 = LLONG_MIN; // f[x][0] 和 f[x][1]
      for (auto &y : g[x]) {
        if (y != fa) {
          auto [r0, r1] = dfs(y, x);
          long long t = max(f1 + r0, f0 + r1);
          f0 = max(f0 + r0, f1 + r1);
          f1 = t;
        }
      }
      return {max(f0 + nums[x], f1 + (nums[x] ^ k)), max(f1 + nums[x], f0 + (nums[x] ^ k))};
    };
    return dfs(0, -1).first;
  }
};