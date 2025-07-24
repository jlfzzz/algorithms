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
  int minSwaps(vector<int> &nums) {
    int n = nums.size();
    vector<tuple<int, int, int>> record(n);

    auto digit_sum = [&](int x) -> int {
      int sum = 0;
      while (x > 0) {
        sum += x % 10;
        x /= 10;
      }
      return sum;
    };

    for (int i = 0; i < n; i++) {
      record[i] = make_tuple(digit_sum(nums[i]), nums[i], i);
    }

    ranges::sort(record, [](auto &a, auto& b) {
      if (get<0>(a) != get<0>(b)) {
        return get<0>(a) < get<0>(b);
      }
      return get<1>(a) < get<1>(b);
    });

    int ans = 0;
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
      pos[i] = get<2>(record[i]);
    }

    for (int i = 0; i < n; i++) {
      while (pos[i] != i) {
        swap(pos[i], pos[pos[i]]);
        ans++;
      }
    }
    return ans;
  }
}