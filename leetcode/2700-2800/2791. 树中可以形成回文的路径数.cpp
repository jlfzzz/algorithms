//
// Created by 123 on 25-5-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  long long countPalindromePaths(vector<int> &parent, string s) {
    int n = parent.size();
    vector<vector<int>> graph(n, vector<int>());

    for (int i = 1; i < n; i++) {
      graph[parent[i]].push_back(i);
    }

    unordered_map<int, int> map;
    map[0] = 1;
    ll ans = 0;
    auto dfs = [&](this auto &&dfs, int curr, int curr_xor) -> void {
      curr_xor = curr_xor ^ (1 << (s[curr] - 'a'));
      ans += map[curr_xor];
      for (int i = 0; i < 26; i++) {
        ans += map[curr_xor ^ (1 << i)];
      }
      map[curr_xor]++;
      for (int child: graph[curr]) {
        dfs(child, curr_xor);
      }
    };
    for (int child: graph[0]) {
      dfs(child, 0);
    }
    return ans;
  }
};


class Solution {
public:
  long long countPalindromePaths(vector<int> &parent, string s) {
    int n = parent.size();
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 1; i < n; i++) {
      graph[parent[i]].push_back(i);
    }

    unordered_map<int, int> mp;
    mp[0] = 1;
    ll ans = 0;
    auto dfs = [&](this auto &&dfs, int fa, int curr_xor) -> void {
      ans += mp[curr_xor];
      for (int child: graph[fa]) {
        int new_xor = curr_xor ^ (1 << (s[child] - 'a'));
        for (int i = 0; i < 26; i++) {
          ans += mp[new_xor ^ (1 << i)];
        }
        mp[new_xor]++;
        dfs(child, new_xor);
      }
    };
    dfs(0, 0);
    return ans - 1;
  }
};

class Solution2 {
public:
  long long countPalindromePaths(vector<int> &parent, string s) {
    int n = parent.size();
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
      int fa = parent[i];
      g[fa].push_back(i);
    }

    long long ans = 0;
    unordered_map<int, int> cnt;
    cnt[0] = 1;
    auto dfs = [&](this auto &&dfs, int fa, int curr_xor) -> void {
      for (int child: g[fa]) {
        int x = curr_xor ^ (1 << (s[child] - 'a'));
        ans += cnt.contains(x) ? cnt[x] : 0;
        for (int i = 0; i < 26; i++) {
          ans += cnt.contains(x ^ (1 << i)) ? cnt[x ^ (1 << i)] : 0;
        }
        cnt[x]++;
        dfs(child, x);
      }
    };
    dfs(0, 0);
    return ans;
  }
};
