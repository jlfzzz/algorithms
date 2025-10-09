#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;

// 总结：主要就是更新方向 子集 -> 超集 or 超集-> 子集。

/*
“哪一层在外”取决于依赖方向是否会“回头再补”。
当是“超集→子集”（向下推）时，必须按“按位分维度”的顺序（bit 在外、mask在内）做分层传递，保证传递具有传递性（超集的超集先汇总，再下推）。 当是“子集→超集”（向上推）时，只要外层遍历 mask
的顺序是拓扑顺序（加一位后编号一定更大），就能一路向上推到所有超集；因此“mask 在外、bit 在内”也成立。
*/

// codeforces 1208 F, 165 E

// lc 3670

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
