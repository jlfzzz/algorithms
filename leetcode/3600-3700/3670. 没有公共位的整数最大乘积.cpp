#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;


class Solution {
public:
    long long maxProduct(vector<int> &nums) {
        int w = bit_width((uint32_t) ranges::max(nums));
        int u = 1 << w;
        vector<int> f(u);
        for (int x: nums) {
            f[x] = x;
        }

        for (int i = 0; i < w; i++) {
            for (int j = 0; j < u; j++) {
                if (j >> i & 1) {
                    f[j] = max(f[j], f[j ^ (1 << i)]);
                }
            }
        }

        long long ans = 0;
        for (int x: nums) {
            ans = max(ans, 1LL * x * f[(u - 1) ^ x]);
        }
        return ans;
    }
};
