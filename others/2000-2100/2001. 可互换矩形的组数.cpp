#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std; //
// Created by 123 on 25-5-19.
//

class Solution {
public:
  long long interchangeableRectangles(vector<vector<int>> &rectangles) {
    unordered_map<string, long long> cnt;
    long long ans = 0;
    for (auto &v: rectangles) {
      int a = v[0], b = v[1];
      int g = gcd(a, b);
      // 用字符串做key，也可以用pair<int,int>
      string key = to_string(a / g) + "/" + to_string(b / g);
      ans += cnt[key]++;
    }
    return ans;
  }
  // C++17 及以上可以直接用 std::gcd
  int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
};

class Solution2 {
public:
  long long interchangeableRectangles(vector<vector<int>> &rectangles) {
    long long ans = 0;
    unordered_map<long long, long long> map;
    for (auto &v: rectangles) {
      int a = v[0];
      int b = v[1];
      long long c = a * 1.0 / b * 1e10;
      ans += map[c]++;
    }
    return ans;
  }
};
