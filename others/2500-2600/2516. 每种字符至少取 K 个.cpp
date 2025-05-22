//
// Created by 123 on 25-5-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int takeCharacters(string s, int k) {
    vector<int> record(3, 0);
    vector<int> window(3, 0);
    for (char c : s) {
      record[c - 'a']++;
    }

    for (int i = 0; i < 3; i++) {
      window[i] = record[i] - k;
      if (window[i] < 0) {
        return -1;
      }
    }

    int n = s.size();
    int left = 0;
    int ans = 0;
    for (int right = 0; right < n; right++) {
      char c = s[right];
      window[c - 'a']--;
      while (window[c - 'a'] < 0) {
        window[s[left++] - 'a']++;
      }
      ans = max(ans, right - left + 1);
    }
    return n - ans;
  }
};