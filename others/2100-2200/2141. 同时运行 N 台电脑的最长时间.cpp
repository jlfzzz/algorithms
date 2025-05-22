//
// Created by 123 on 25-5-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  long long maxRunTime(int n, vector<int>& batteries) {
    ll sum = reduce(batteries.begin(), batteries.end(), 0LL);
    ll l = 0;
    ll r = sum / n + 1e5;
    ll ans = 0;
    while (l < r) {
      ll mid = l + (r - l) / 2;
      ll temp = 0;
      for (ll b : batteries) {
        temp += min(b, mid);
      }
      if (temp >= n * mid * 1LL) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return ans;
  }
};