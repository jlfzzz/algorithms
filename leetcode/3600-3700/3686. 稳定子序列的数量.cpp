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
