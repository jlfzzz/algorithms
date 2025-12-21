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
    int maxSum(vector<int> &nums, int k, int m) {
        int n = nums.size();
        vvi dp(n + 1, vi(k + 1, -inf));
        vvi pre(n + 1, vi(k + 1, -inf));
        vi pref(n + 1);

        F(i, 1, n) { pref[i] = pref[i - 1] + nums[i - 1]; }

        dp[0][0] = pre[0][0] = 0;

        F(i, 1, n) {
            F(j, 0, k) {
                dp[i][j] = dp[i - 1][j];

                if (i - m >= 0 && j > 0) {
                    dp[i][j] = max(dp[i][j], pre[i - m][j - 1] + pref[i]);
                }

                pre[i][j] = max(dp[i][j] - pref[i], pre[i - 1][j]);
            }
        }

        return dp[n][k];
    }
};
