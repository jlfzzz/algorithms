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
    int minCost(vector<vector<int>> &grid, int k) {
        vector<tuple<int, int, int>> a;
        int n = SZ(grid);
        int m = SZ(grid[0]);

        F(i, 0, n - 1) {
            F(j, 0, m - 1) { a.pb(grid[i][j], i, j); }
        }

        ranges::sort(a, greater<>());

        vvi dp(n, vi(m, inf));
        dp[0][0] = 0;

        F(round, 0, k) {
            F(i, 0, n - 1) {
                F(j, 0, m - 1) {
                    if (i - 1 >= 0) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j]);
                    }
                    if (j - 1 >= 0) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j]);
                    }
                }
            }

            if (round < k) {
                vvi ndp = dp;
                int mn = inf;

                for (int i = 0; i < SZ(a);) {
                    int j = i;
                    int val = get<0>(a[i]);

                    int mn2 = inf;
                    while (j < SZ(a) && get<0>(a[j]) == val) {
                        auto [v, x, y] = a[j];
                        mn2 = min(mn2, dp[x][y]);
                        j++;
                    }

                    mn = min(mn, mn2);

                    int idx = i;
                    while (idx < j) {
                        auto [v, x, y] = a[idx];
                        ndp[x][y] = min(ndp[x][y], mn);
                        idx++;
                    }

                    i = j;
                }
                dp.swap(ndp);
            }
        }

        return dp[n - 1][m - 1];
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
