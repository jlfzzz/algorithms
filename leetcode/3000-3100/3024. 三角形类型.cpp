//
// Created by 123 on 25-5-19.
//

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>
#include <memory>
#include <map>
#include <queue>
#include <cstring>
#include <array>
#include <bitset>
#include <stack>
#include <set>
#include <random>
using namespace std;
class Solution {
public:
  string triangleType(vector<int>& nums) {
    int a = nums[0];
    int b = nums[1];
    int c = nums[2];

    if (a == b && a == c && b == c) {
      return "equilateral";
    } else {
      if (a + b > c && abs(a - b) < c) {
        if (a == b || a == c || b == c) {
          return "isosceles";
        }
        return "scalene";
      } else {
        return "none";
      }
    }
  }
};
