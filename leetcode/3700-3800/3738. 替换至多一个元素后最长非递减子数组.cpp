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
    int longestSubarray(vector<int> &nums) {
        int n = SZ(nums);
        vi pre(n), suf(n);
        pre[0] = suf[n - 1] = 1;
        F(i, 1, n - 1) {
            if (nums[i] >= nums[i - 1]) {
                pre[i] = pre[i - 1] + 1;
            } else {
                pre[i] = 1;
            }
        }
        D(i, n - 2, 0) {
            if (nums[i] <= nums[i + 1]) {
                suf[i] = suf[i + 1] + 1;
            } else {
                suf[i] = 1;
            }
        }

        int ans = max(ranges::max(pre), ranges::max(suf));
        if (ans < n) {
            ans++;
        }

        F(i, 1, n - 2) {
            if (nums[i + 1] >= nums[i - 1]) {
                ans = max(ans, 1 + pre[i - 1] + suf[i + 1]);
            }
        }

        return ans;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
