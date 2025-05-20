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
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  int numEquivDominoPairs(vector<vector<int>> &dominoes) {
    int n = dominoes.size();
    unordered_map<string, int> s;
    int ans = 0;
    for (auto &v: dominoes) {
      int mn = min(v[0], v[1]);
      int mx = max(v[0], v[1]);
      ans += s[to_string(mn) + "/" + to_string(mx)]++;
    }

    return ans;
  }
};

class Solution2 {
public:
  int numEquivDominoPairs(vector<vector<int>> &dominoes) {
    int cnt[10][10] = {};
    int ans = 0;
    for (auto d: dominoes) {
      int a = min(d[0], d[1]);
      int b = max(d[0], d[1]);
      ans += cnt[a][b];
      cnt[a][b]++;
    }
    return ans;
  }
};

class Solution3 {
public:
  int numEquivDominoPairs(vector<vector<int>> &dominoes) {
    unordered_map<string, int> mp;
    for (auto &v: dominoes) {
      string s1 = to_string(v[0]) + to_string(v[1]);
      string s2 = to_string(v[1]) + to_string(v[0]);
      if (!mp[s1] && !mp[s2]) {
        mp[s1]++;
      } else {
        if (mp[s1]) {
          mp[s1]++;
        } else {
          mp[s2]++;
        }
      }
    }

    int ans = 0;
    for (auto &p: mp) {
      if (p.second >= 2) {
        ans += (p.second * (p.second - 1)) / 2;
      }
    }
    return ans;
  }
};
