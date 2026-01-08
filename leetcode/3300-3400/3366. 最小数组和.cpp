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
    int minArraySum(vector<int> &nums, int k, int op1, int op2) {
        vvi dp(op1 + 1, vi(op2 + 1, inf));
        dp[0][0] = 0;

        auto chk = [&](int &val1, int x) {
            if (x < val1) {
                val1 = x;
            }
        };

        for (int x: nums) {
            int val1 = (x + 1) / 2;
            int val2 = val1 - k;
            int val3 = x - k;
            int val4 = (val3 + 1) / 2;

            vvi ndp(op1 + 1, vi(op2 + 1, inf));
            F(i, 0, op1) {
                F(j, 0, op2) {
                    if (dp[i][j] == inf)
                        continue;
                    chk(ndp[i][j], dp[i][j] + x);
                    if (i + 1 <= op1) {
                        chk(ndp[i + 1][j], dp[i][j] + val1);
                        if (j + 1 <= op2 && val1 >= k) {
                            chk(ndp[i + 1][j + 1], dp[i][j] + val2);
                        }
                    }
                    if (j + 1 <= op2 && x >= k) {
                        chk(ndp[i][j + 1], dp[i][j] + val3);
                        if (i + 1 <= op1) {
                            chk(ndp[i + 1][j + 1], dp[i][j] + val4);
                        }
                    }
                }
            }

            dp.swap(ndp);
        }

        int ans = inf;
        for (auto &v: dp) {
            ans = min(ans, ranges::min(v));
        }

        return ans;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
