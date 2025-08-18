#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;


class Solution {
public:
    long long minArraySum(vector<int> &nums, int k) {
        int n = nums.size();
        unordered_map<ll, ll> last;
        last[0] = 0;
        vector<ll> dp(n + 1, 0ll);
        ll pre = 0;

        for (int i = 1; i <= n; ++i) {
            pre = (1ll * pre + nums[i - 1]) % k;
            dp[i] = dp[i - 1] + nums[i - 1];
            if (last.find(pre) != last.end()) {
                int j = last[pre];
                dp[i] = min(dp[i], dp[j]);
            }
            last[pre] = i;
        }

        return dp[n];
    }
};
