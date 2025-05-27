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
  int similarPairs(vector<string>& words) {
    int n = words.size();
    unordered_map<int, int> counts;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int mask = 0;
      for (char c : words[i]) {
        mask = mask | (1 << (c - 'a'));
      }
      ans += counts[mask]++;
    }
    return ans;
  }
};