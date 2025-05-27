//
// Created by 123 on 25-5-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
    vector<int> mins(26, INT_MAX);
    int n = points.size();
    int min2 = INT_MAX;
    for (int i = 0; i < n; i++) {
      int x = points[i][0];
      int y = points[i][1];
      int offset = s[i] - 'a';
      int mx = max(abs(x), abs(y));
      if (mx < mins[offset]) {
        min2 = min(min2, mins[offset]);
        mins[offset] = mx;
      } else {
        min2 = min(min2, mx);
      }
    }

    int ans = 0;
    for (int d : mins) {
      ans += d < min2;
    }
    return ans;
  }
};

class Solution2 {
public:
  int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
    int n = points.size();
    int ans = 0;
    int lo = 0;
    int hi = INT_MAX / 2;

    auto check = [&](int len, int& curr) -> bool {
      unordered_set<char> set;
      for (int i = 0; i < n; i++) {
        auto& p = points[i];
        int x = p[0], y = p[1];
        if (abs(x) <= len && abs(y) <= len) {
          if (set.contains(s[i])) {
            return false;
          } else {
            set.insert(s[i]);
            curr++;
          }
        }
      }
      return true;
    };

    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      int curr = 0;
      if (check(mid, curr)) {
        ans = curr;
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return ans;
  }
};