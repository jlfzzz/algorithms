#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_map = tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multiset =
    tree<pair<long long, long long>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int N = int(5e5 + 5);
int INIT = [] { return 0; }();

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
    int maxPathScore(vector<vector<int>> &grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        int mx = min(m + n + 10, k);
        vector dp(m, vector(n, vector(mx + 1, -1)));
        int t1 = grid[0][0];
        if (t1 > k) {
            return -1;
        }
        dp[0][0][t1] = t1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    continue;
                }
                int cur = grid[i][j];
                int cost = 0;
                if (grid[i][j] > 0) {
                    cost = 1;
                }
                for (int l = 0; l + cost <= mx; l++) {
                    if (i > 0 && dp[i - 1][j][l] != -1) {
                        dp[i][j][l + cost] = max(dp[i][j][l + cost], dp[i - 1][j][l] + cur);
                    }

                    // cerr << j << endl;
                    if (j > 0 && dp[i][j - 1][l] != -1) {
                        dp[i][j][l + cost] = max(dp[i][j][l + cost], dp[i][j - 1][l] + cur);
                    }
                }
            }
        }

        int ans = ranges::max(dp[m - 1][n - 1]);
        return ans;
    }
};
