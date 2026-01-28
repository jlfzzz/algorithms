#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_map>
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
    int comb2(int num) { return num * (num - 1) / 2; }

public:
    int subsequencesWithMiddleMode(vector<int> &nums) {
        int n = nums.size();
        long long ans = 1LL * n * (n - 1) * (n - 2) * (n - 3) * (n - 4) / 120; // 所有方案数
        unordered_map<int, int> pre, suf;
        for (int x: nums) {
            suf[x]++;
        }
        // 枚举 x，作为子序列正中间的数
        for (int left = 0; left < n - 2; left++) {
            int x = nums[left];
            suf[x]--;
            if (left > 1) {
                int right = n - 1 - left;
                int pre_x = pre[x], suf_x = suf[x];
                // 不合法：只有一个 x
                ans -= 1LL * comb2(left - pre_x) * comb2(right - suf_x);
                // 不合法：只有两个 x，且至少有两个 y（y != x）
                for (auto &[y, suf_y]: suf) { // 注意 suf_y 可能是 0
                    if (y == x) {
                        continue;
                    }
                    int pre_y = pre[y];
                    // 左边有两个 y，右边有一个 x，即 yy x xz（z 可以等于 y）
                    ans -= 1LL * comb2(pre_y) * suf_x * (right - suf_x);
                    // 右边有两个 y，左边有一个 x，即 zx x yy（z 可以等于 y）
                    ans -= 1LL * comb2(suf_y) * pre_x * (left - pre_x);
                    // 左右各有一个 y，另一个 x 在左边，即 xy x yz（z != y）
                    ans -= 1LL * pre_y * suf_y * pre_x * (right - suf_x - suf_y);
                    // 左右各有一个 y，另一个 x 在右边，即 zy x xy（z != y）
                    ans -= 1LL * pre_y * suf_y * suf_x * (left - pre_x - pre_y);
                }
            }
            pre[x]++;
        }
        return ans % 1'000'000'007;
    }
};


// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
