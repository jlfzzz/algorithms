#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
public:
    int numOfWays(int n) {
        const int MOD = 1e9 + 7;

        vector<int> valid;
        for (int mask = 0; mask < 27; ++mask) {
            int c0 = mask % 3;
            int c1 = (mask / 3) % 3;
            int c2 = (mask / 9) % 3;

            if (c0 != c1 && c1 != c2) {
                valid.push_back(mask);
            }
        }

        vector<vector<int>> adj(27);
        for (int curr: valid) {
            for (int prev: valid) {
                bool f = true;
                int t1 = curr;
                int t2 = prev;

                for (int k = 0; k < 3; ++k) {
                    if ((t1 % 3) == (t2 % 3)) {
                        f = false;
                        break;
                    }
                    t1 /= 3;
                    t2 /= 3;
                }

                if (f) {
                    adj[curr].push_back(prev);
                }
            }
        }

        vector<ll> dp(27, 0);
        for (int mask: valid) {
            dp[mask] = 1;
        }

        for (int i = 1; i < n; ++i) {
            vector<ll> ndp(27, 0);

            for (int curr: valid) {
                for (int prev: adj[curr]) {
                    ndp[curr] = (ndp[curr] + dp[prev]) % MOD;
                }
            }
            dp = ndp;
        }

        ll ans = 0;
        for (int mask: valid) {
            ans = (ans + dp[mask]) % MOD;
        }

        return ans;
    }
};
