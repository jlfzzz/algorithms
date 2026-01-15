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
    int countSubMultisets(vector<int> &nums, int l, int r) {
        int total = 0;
        for (int x: nums)
            total += x;

        r = min(r, total);

        unordered_map<int, int> cnt;
        for (int x: nums)
            cnt[x]++;

        vi dp(r + 1, 0);
        dp[0] = 1;

        for (auto [x, c]: cnt) {
            if (x == 0) {
                continue;
            }

            F(j, x, r) { dp[j] = (dp[j] + dp[j - x]) % MOD; }

            int step = (c + 1) * x;
            D(j, r, step) { dp[j] = (dp[j] - dp[j - step] + MOD) % MOD; }
        }

        ll ans = 0;
        F(i, l, r) { ans = (ans + dp[i]) % MOD; }

        return (ans * (cnt[0] + 1) % MOD);
    }
};

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     Solution sol;
// }
