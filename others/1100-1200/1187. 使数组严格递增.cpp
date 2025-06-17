#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

class Solution {
public:
    int makeArrayIncreasing(vector<int> &arr1, vector<int> &arr2) {
        ranges::sort(arr2);
        int n = arr1.size();
        unordered_map<int, int> mp[n];

        auto dfs = [&](this auto &&dfs, int i, int prev) -> int {
            if (i < 0) {
                return 0;
            }

            if (auto it = mp[i].find(prev); it != mp[i].end()) {
                return it->second;
            }

            int res = arr1[i] < prev ? dfs(i - 1, arr1[i]) : INT_MAX / 2;
            auto k = ranges::lower_bound(arr2, prev);
            if (k != arr2.begin()) {
                res = min(res, dfs(i - 1, *--k) + 1);
            }
            mp[i][prev] = res;
            return res;
            };

        int ans = dfs(n - 1, INT_MAX);
        return ans == INT_MAX / 2 ? -1 : ans;
    }
};