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
