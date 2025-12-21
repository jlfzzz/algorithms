#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)


class Solution {
public:
    long long maximumStrength(vector<int> &nums, int k) {
        int n = nums.size();
        vvl dp(n + 1, vl(k + 1, -INF));
        vvl pre(n + 1, vl(k + 1, -INF));
        vl pref(n + 1);

        F(i, 1, n) { pref[i] = pref[i - 1] + nums[i - 1]; }

        dp[0][0] = pre[0][0] = 0;

        F(i, 1, n) {
            F(j, 0, k) {
                dp[i][j] = dp[i - 1][j];

                if (j > 0) {
                    ll sign = 1;
                    if (j % 2 == 0) {
                        sign = -1;
                    }
                    ll x = k - j + 1;
                    dp[i][j] = max(dp[i][j], pre[i - 1][j - 1] + sign * x * pref[i]);
                }

                if (j < k) {
                    ll nj = j + 1;
                    ll ns = 1;
                    if (nj % 2 == 0) {
                        ns = -1;
                    }
                    ll nx = k - nj + 1;

                    pre[i][j] = max(pre[i - 1][j], dp[i][j] - ns * nx * pref[i]);
                }
            }
        }

        return dp[n][k];
    }
};
