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
  vector<int> findWordsContaining(vector<string>& words, char x) {
    vector<int> ans;
    for (int i = 0; i < words.size(); i++) {
      if (words[i].contains(x)) {
        ans.push_back(i);
      }
    }
    return ans;
  }
};