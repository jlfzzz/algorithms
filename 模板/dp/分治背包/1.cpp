#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 结论题 分治优化
// https://codeforces.com/problemset/problem/1442/D


class Solution {
public:
    int brilliantSurprise(vector<vector<int>> &present, int limit) {
        int n = present.size();

        vector<int> sum(n);
        for (int i = 0; i < n; i++) {
            for (int x: present[i])
                sum[i] += x;
        }

        int ans = 0;
        vector<int> dp(limit + 1, 0);

        auto dfs = [&](this auto &&dfs, int l, int r, vector<int> &dp) -> void {
            if (l == r) {
                vector<int> base = dp;
                int pre = 0;
                int sz = present[l].size();
                for (int i = 0; i <= sz && i <= limit; i++) {
                    if (i > 0)
                        pre += present[l][i - 1];
                    for (int j = i; j <= limit; j++) {
                        dp[j] = max(dp[j], base[j - i] + pre);
                    }
                }
                ans = max(ans, dp[limit]);
                return;
            }

            int mid = (l + r) / 2;
            vector<int> temp = dp;

            for (int i = l; i <= mid; i++) {
                int sz = present[i].size();
                if (sz > limit)
                    continue;
                for (int j = limit; j >= sz; j--) {
                    dp[j] = max(dp[j], dp[j - sz] + sum[i]);
                }
            }
            dfs(mid + 1, r, dp);

            dp = temp;

            for (int i = mid + 1; i <= r; i++) {
                int sz = present[i].size();
                if (sz > limit)
                    continue;
                for (int j = limit; j >= sz; j--) {
                    dp[j] = max(dp[j], dp[j - sz] + sum[i]);
                }
            }
            dfs(l, mid, dp);
        };

        dfs(0, n - 1, dp);
        return ans;
    }
};
