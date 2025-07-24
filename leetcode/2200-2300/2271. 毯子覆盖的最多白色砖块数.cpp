//
// Created by 123 on 25-5-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
    sort(tiles.begin(), tiles.end());
    int n = tiles.size();
    vector<int> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
      prefix_sum[i + 1] = prefix_sum[i] + tiles[i][1] - tiles[i][0] + 1;
    }
    int ans = 0;
    for (int left = 0; left < n; left++) {
      int carpet_end = tiles[left][0] + carpetLen - 1;
      // 找到第一个 tile 的左端点 > carpet_end 的下标
      int l = left, r = n;
      while (l < r) {
        int mid = (l + r) / 2;
        if (tiles[mid][0] > carpet_end) r = mid;
        else l = mid + 1;
      }
      int right = l - 1; // right 是最后一个地毯能覆盖到的 tile
      int total = prefix_sum[right + 1] - prefix_sum[left];
      // 如果最后一块 tile 只被部分覆盖
      if (tiles[right][1] > carpet_end) {
        total -= tiles[right][1] - carpet_end;
      }
      ans = max(ans, total);
    }
    return ans;
  }
};
