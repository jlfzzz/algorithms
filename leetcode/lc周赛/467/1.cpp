#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

class Solution {
public:
    int countStableSubsequences(vector<int> &nums) {
        int n = nums.size();

        vector<vector<ll>> dp(n + 1, vector<ll>(4));
        int pre_odd = 0, pre_even = 0;
        for (int i = 1; i <= n; i++) {
            int cur = nums[i - 1];
            for (int j = 0; j < 4; j++) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }

            if (cur & 1) {
                dp[i][2] = (dp[i][2] + 1) % MOD;
                dp[i][2] = (dp[i][2] + dp[pre_even][0] + dp[pre_even][1]) % MOD;
                dp[i][3] = (dp[i][3] + dp[pre_odd][2]) % MOD;

                pre_odd = i;
            } else {
                dp[i][0] = (dp[i][0] + 1) % MOD;
                dp[i][0] = (dp[i][0] + dp[pre_odd][2] + dp[pre_odd][3]) % MOD;
                dp[i][1] = (dp[i][1] + dp[pre_even][0]) % MOD;

                pre_even = i;
            }
        }

        ll ans = 0;
        for (int j = 0; j < 4; j++) {
            ans = (ans + dp[n][j]) % MOD;
        }
        return ans;
    }
};



class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int> &nums, int k) {
        int n = nums.size();
        vector<bool> ans(n);

        bitset<4001> dp, temp;
        dp[0] = 1;

        vector<int> freq(n + 2, 0);
        for (int x: nums) {
            if (x <= n)
                freq[x]++;
            else
                freq[n + 1]++;
        }

        vector<int> eq(n + 2, 0), ge(n + 2, 0);
        for (int i = 1; i <= n; i++)
            eq[i] = freq[i];
        for (int i = n; i >= 1; i--)
            ge[i] = ge[i + 1] + freq[i];

        for (int i = 0; i < n; i++) {
            temp = dp;

            int cnt1 = ge[i + 1];
            int cnt2 = eq[i + 1];

            int use1 = min(cnt1, k / (i + 1));
            for (int t = 1; use1 > 0; t <<= 1) {
                int take = min(t, use1);
                temp |= (temp << ((i + 1) * take));
                use1 -= take;
            }

            if (temp[k])
                ans[i] = true;

            int use2 = min(cnt2, k / (i + 1));
            for (int t = 1; use2 > 0; t <<= 1) {
                int take = min(t, use2);
                dp |= (dp << ((i + 1) * take));
                use2 -= take;
            }
        }

        return ans;
    }
};






class Solution {
public:
    vector<int> maxKDistinct(vector<int> &nums, int k) {
        ranges::sort(nums, greater<>());
        unordered_set<int> vis;
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (k > 0) {
                if (!vis.contains(nums[i])) {
                    ans.push_back(nums[i]);
                    vis.insert(nums[i]);
                    k--;
                }
            } else {
                break;
            }
        }

        return ans;
    }
};






class Solution {
public:
    int earliestTime(vector<vector<int>> &tasks) {
        int ans = inf;
        for (auto &v: tasks) {
            int s = v[0], e = v[1];
            ans = min(ans, s + e);
        }
        return ans;
    }
};
