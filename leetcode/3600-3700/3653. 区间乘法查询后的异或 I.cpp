#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;


class Solution {
public:
    int xorAfterQueries(vector<int> &nums, vector<vector<int>> &queries) {
        int n = nums.size();

        for (auto &q: queries) {
            ll l = q[0], r = q[1], k = q[2], v = q[3];
            for (int i = l; i <= r; i += k) {
                nums[i] = (1ll * nums[i] * v) % MOD;
            }
        }

        int ans = 0;
        for (int x: nums) {
            ans ^= x;
        }
        return ans;
    }
};
