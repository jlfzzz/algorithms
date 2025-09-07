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
    int countBinaryPalindromes(long long n) {
        if (n == 0) {
            return 1;
        }

        int m = bit_width((ull) n);

        vector<vector<int>> memo(100, vector<int>(2, -1));
        auto dfs = [&](this auto &&dfs, int i, bool is_hi) -> int {
            if (i < m / 2) {
                return 1;
            }

            if (memo[i][is_hi] != -1) {
                return memo[i][is_hi];
            }

            int lo = 0;
            int hi = is_hi ? ((ll) n >> i & 1) : 1;

            int res = 0;
            if (!is_hi) {
                res = 2 * dfs(i - 1, false);
            } else {
                for (int j = lo; j <= hi; j++) {
                    res += dfs(i - 1, is_hi && j == ((ll) n >> i & 1));
                }
            }

            memo[i][is_hi] = res;
            return res;
        };

        int equal = (m == 1 ? 1 : dfs(m - 2, true));

        ll left = (ll) n >> (m - (m + 1) / 2);
        ll pal = left;
        ll tmp = left >> (m & 1);
        for (int t = 0; t < m / 2; t++) {
            pal = (pal << 1) | ((tmp >> t) & 1);
        }
        if (pal > (ll) n) {
            equal--;
        }

        int ans = 1; // 计入 0
        for (int L = 1; L < m; L++) {
            ans += 1 << ((L - 1) / 2);
        }
        ans += equal;

        return ans;
    }
};
