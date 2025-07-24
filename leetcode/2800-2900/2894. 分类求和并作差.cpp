//
// Created by 32098 on 25-5-27.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int differenceOfSums(int n, int m) {
    return n * (n + 1) / 2 - n / m * (n / m + 1) * m;
  }
};

class Solution2 {
public:
  int differenceOfSums(int n, int m) {
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 1; i <= n; i++) {
      if (i % m != 0) {
        sum1 += i;
      } else {
        sum2 += i;
      }
    }
    return sum1 - sum2;
  }
};

