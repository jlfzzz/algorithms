#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
const ll MOD2 = 4611686018427387847;
constexpr int inf = 100'000'005;
class Solution {
public:
    int kInversePairs(int n, int k) {
        vector dp(k + 1, 0ll);
        dp[0] = 1;

        for (int i = 2; i <= n; i++) {
            auto t = dp;
            ll pre = 0;
            for (int j = 0; j <= k; j++) {
                pre = (pre + dp[j]) % MOD;
                if (j - i >= 0) {
                    pre = (pre - dp[j - i] + MOD) % MOD;
                }
                t[j] = pre;
            }
            dp = std::move(t);
        }
        return dp[k];
    }
};
