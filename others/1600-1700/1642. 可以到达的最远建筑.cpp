//
// Created by 123 on 25-5-19.
//

#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
  int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    int n = heights.size();
    // 由于我们需要维护最大的 l 个值，因此使用小根堆
    priority_queue<int, vector<int>, greater<int>> q;
    // 需要使用砖块的 delta h 的和
    int sumH = 0;
    for (int i = 1; i < n; ++i) {
      int deltaH = heights[i] - heights[i - 1];
      if (deltaH > 0) {
        q.push(deltaH);
        // 如果优先队列已满，需要拿出一个其中的最小值，改为使用砖块
        if (q.size() > ladders) {
          sumH += q.top();
          q.pop();
        }
        if (sumH > bricks) {
          return i - 1;
        }
      }
    }
    return n - 1;
  }
};

class Solution {
public:
  int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    int n = heights.size();
    int lo = 0, hi = n;
    int ans = hi;

    auto check = [&](int target) -> bool {
      if (ladders >= target) {
        return true;
      }

      vector<int> record(target);
      for (int i = 0; i < target; i++) {
        if (heights[i + 1] > heights[i]) {
          record[i] = heights[i + 1] - heights[i];
        }
      }
      ranges::sort(record);
      long long sum = accumulate(record.begin(), record.end(), 0LL);
      for (int i = record.size() - 1, temp = ladders; temp > 0; i--, temp--) {
        sum -= record[i];
      }
      return sum <= bricks;
    };

    while (lo < hi) {
      if (const int mid = lo + (hi - lo) / 2; check(mid)) {
        ans = mid;
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return ans;
  }
};