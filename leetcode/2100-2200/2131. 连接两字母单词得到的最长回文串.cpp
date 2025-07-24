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
  int longestPalindrome(vector<string>& words) {
    unordered_map<string, int> mp;
    int ans = 0;
    for (auto& s : words) {
      string ss = string() + s[1] + s[0]; // 反转字符串
      if (mp.count(ss) && mp[ss] > 0) {
        ans += 4;
        mp[ss]--;
      } else {
        mp[s]++;
      }
    }
    // 检查是否有可以放在中间的对称串
    for (auto& p : mp) {
      const string& s = p.first;
      if (s[0] == s[1] && p.second > 0) {
        ans += 2;
        break;
      }
    }
    return ans;
  }
};