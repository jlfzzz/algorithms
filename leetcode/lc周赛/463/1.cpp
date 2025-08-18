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
    long long maxProfit(vector<int> &prices, vector<int> &strategy, int k) {
        int n = prices.size();

        vector<ll> pre1(n + 1);
        vector<ll> pre2(n + 1);
        for (int i = 1; i <= n; i++) {
            pre1[i] = 1ll * pre1[i - 1] + 1ll * prices[i - 1] * strategy[i - 1];
            pre2[i] = 1ll * pre2[i - 1] + 1ll * prices[i - 1];
        }

        ll ans = pre1[n];

        for (int i = 1; i + k - 1 <= n; i++) {
            ll t1 = pre1[n] - pre1[i + k - 1] + pre1[i - 1];
            ll t2 = pre2[i + k - 1] - pre2[i + k / 2 - 1];
            ans = max(ans, t1 + t2);
        }
        return ans;
    }
};
