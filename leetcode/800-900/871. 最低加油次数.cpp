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
    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations) {
        int n = stations.size();
        vi dp(n + 10);
        dp[0] = startFuel;

        F(i, 0, n - 1) {
            auto &v = stations[i];
            D(j, i, 0) {
                if (dp[j] >= v[0]) {
                    dp[j + 1] = max(dp[j + 1], dp[j] + v[1]);
                }
            }
        }
        F(i, 0, n) {
            if (dp[i] >= target) {
                return i;
            }
        }

        return -1;
    }
};
