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
    int minDistance(vector<int> &houses, int k) {
        sort(all(houses));
        int n = SZ(houses);

        vvi cost(n, vi(n, 0));
        F(len, 2, n) {
            F(i, 0, n - len) {
                int j = i + len - 1;
                cost[i][j] = cost[i + 1][j - 1] + (houses[j] - houses[i]);
            }
        }

        vvi dp(n + 1, vi(k + 1, inf));
        dp[0][0] = 0;

        F(j, 1, k) {
            F(i, 1, n) {
                F(p, 0, i - 1) {
                    if (dp[p][j - 1] != inf) {
                        dp[i][j] = min(dp[i][j], dp[p][j - 1] + cost[p][i - 1]);
                    }
                }
            }
        }

        return dp[n][k];
    }
};
