#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };
constexpr int MOD = int(1e9 + 7);


class Solution {
public:
    int minimumDifference(vector<int> &nums) {
        int total = reduce(nums.begin(), nums.end(), 0);
        int half = total / 2;

        auto count = [&](const vector<int> &nums) -> unordered_map<int, vector<int>> {
            unordered_map<int, vector<int>> ret;
            for (int i = 0; i < 1 << nums.size(); ++i) {
                int cnt = 0;
                int s = 0;
                for (int j = 0; j < nums.size(); ++j) {
                    if (i >> j & 1) {
                        cnt += 1;
                        s += nums[j];
                    }
                }
                ret[cnt].emplace_back(s);
            }
            return ret;
            };
        int n = nums.size();
        auto left = count({ nums.begin(), nums.begin() + n / 2 });
        auto right = count({ nums.begin() + n / 2, nums.end() });
        for (auto &[k, v] : right) {
            ranges::sort(v);
        }
        int m = n / 2;
        int ans = INT_MAX;
        for (auto &[k, v] : left) {
            for (int x : v) {
                auto it = ranges::lower_bound(right[m - k], half - x);
                if (it != right[m - k].end()) {
                    ans = min(ans, abs(2 * (x + *it) - total));
                    if (it != right[m - k].begin()) {
                        ans = min(ans, abs(2 * (x + *(prev(it))) - total));
                    }
                }
            }
        }
        return ans;
    }
};