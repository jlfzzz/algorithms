//
// Created by 123 on 25-5-19.
//

#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
  int longestSemiRepetitiveSubstring(string s) {
    bool haveMore = true;
    int n = s.size();
    int ans = 0;
    int left = 0;

    for (int i = 1; i < n; i++) {
      char c = s[i];
      char prev = s[i - 1];

      if (c == prev) {
        if (haveMore) {
          haveMore = false;
        } else {
          while (s[left] != s[left + 1]) {
            left++;
          }
          left++;
        }
      }
      ans = max(i - left + 1, ans);
    }
    return ans == 0 ? 1 : ans;


  }
};
