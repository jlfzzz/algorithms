//
// Created by 123 on 25-5-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int rampartDefensiveLine(vector<vector<int>>& rampart) {
    int hi = INT_MAX;
    int lo = 0;
    int ans = 0;
    int n = rampart.size();

    auto check = [&](int len) -> bool {
      int left = rampart[0][1];
      for (int i = 1; i < n - 1; i++) {
        int before = rampart[i][0] - max(left, rampart[i - 1][1]);
        int after = rampart[i + 1][0] - rampart[i][1];
        if (before + after < len) {
          return false;
        }
        if (before < len) {
          left = rampart[i][1] + len - before;
        }
      }
      return true;
    };

    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        ans = mid;
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return ans;
  }
};