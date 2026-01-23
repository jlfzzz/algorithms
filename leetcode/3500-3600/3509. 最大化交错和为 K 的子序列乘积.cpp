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
    int maxProduct(vector<int> &nums, int k, int limit) {
        int total = reduce(nums.begin(), nums.end());
        if (total < abs(k)) { // |k| 太大
            return -1;
        }

        int n = nums.size(), ans = -1;
        unordered_set<long long> vis;
        auto dfs = [&](this auto &&dfs, int i, int s, int m, bool odd, bool empty) -> void {
            if (ans == limit || m > limit && ans >= 0) { // 无法让 ans 变得更大
                return;
            }

            if (i == n) {
                if (!empty && s == k && m <= limit) { // 合法子序列
                    ans = max(ans, m); // 用合法子序列的元素积更新答案的最大值
                }
                return;
            }

            long long mask = (long long) i << 32 | (s + total) << 15 | m << 2 | odd << 1 | empty;
            if (!vis.insert(mask).second) { // mask 在 vis 中
                return;
            }

            // 不选 x
            dfs(i + 1, s, m, odd, empty);

            // 选 x
            int x = nums[i];
            dfs(i + 1, s + (odd ? -x : x), min(m * x, limit + 1), !odd, false);
        };
        dfs(0, 0, 1, false, true);
        return ans;
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
