//
// Created by 123 on 25-5-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int numPairsDivisibleBy60(vector<int> &time) {
    int ans = 0, cnt[60]{};
    for (int t : time) {
      // 先查询 cnt，再更新 cnt，因为题目要求 i<j
      // 如果先更新，再查询，就把 i=j 的情况也考虑进去了
      ans += cnt[(60 - t % 60) % 60];
      cnt[t % 60]++;
    }
    return ans;
  }
};

class Solution2 {
public:
  int numPairsDivisibleBy60(vector<int>& time) {
    unordered_map<int, int> record;
    int n = time.size();
    int ans = 0;

    for (int i = 0; i < n; i++) {
      int x = time[i];
      for (int j = 60; j < 1200; j += 60) {
        if (j > x && record.contains(j - x)) {
          ans += record[j - x];
        }
      }
      record[x]++;
    }
    return ans;
  }
};