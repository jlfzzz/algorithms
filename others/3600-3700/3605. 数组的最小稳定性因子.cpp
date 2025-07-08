#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int minStable(vector<int> &nums, int maxC) {
        int n = nums.size();
        vector<pair<int, int>> g;
        vector f(n, 0);
        for (int i = 0; i < n; ++i) {
            g.emplace_back(nums[i], i);
            int j = 0;
            for (auto &p : g) {
                p.first = gcd(p.first, nums[i]);
                if (g[j].first == p.first) {
                    g[j].second = p.second;
                } else {
                    g[++j] = move(p);
                }
            }
            g.resize(j + 1);
            if (g[0].first == 1) {
                f[i] = i - g[0].second;
            } else {
                f[i] = i + 1;
            }
        }
        auto check = [&](int target) {
            int cnt = 0;
            for (int i = n - 1; i >= 0; ) {
                if (f[i] > target) {
                    ++cnt;
                    i -= target + 1;
                } else {
                    --i;
                }
            }
            return cnt <= maxC;
            };
        int l = 0, r = n; // 实际上上限最多是 n / (maxC + 1)
        while (l <= r) {
            int m = (l + r) / 2;
            if (check(m)) {
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
};