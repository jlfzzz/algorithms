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
  int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    if (n < m) {
      return 0;
    }

    // 和答案无关的转移可能会溢出，从而报错
    // 为了避免报错，使用 unsigned
    vector f(n + 1, vector<unsigned>(m + 1));
    f[0][0] = 1;
    for (int i = 0; i < n; i++) {
      f[i + 1][0] = 1;
      for (int j = max(m - n + i, 0); j < min(i + 1, m); j++) {
        f[i + 1][j + 1] = f[i][j + 1];
        if (s[i] == t[j]) {
          f[i + 1][j + 1] += f[i][j];
        }
      }
    }
    return f[n][m];
  }
};