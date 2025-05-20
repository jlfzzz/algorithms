//
// Created by 123 on 25-5-20.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr ll MOD = 1'000'000'007;

class Solution {
public:
  int maxNumberOfAlloys(int n, int, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
    int ans = 0;
    int mx = ranges::min(stock) + budget;
    for (auto& comp : composition) {
      auto check = [&](long long num) -> bool {
        long long money = 0;
        for (int i = 0; i < n; i++) {
          if (stock[i] < comp[i] * num) {
            money += (comp[i] * num - stock[i]) * cost[i];
            if (money > budget) {
              return false;
            }
          }
        }
        return true;
      };
      int left = ans, right = mx + 1;
      while (left + 1 < right) { // 开区间写法
        int mid = left + (right - left) / 2;
        (check(mid) ? left : right) = mid;
      }
      ans = left;
    }
    return ans;
  }
};