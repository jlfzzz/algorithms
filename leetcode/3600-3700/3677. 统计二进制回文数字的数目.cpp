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
        int m = bit_width((unsigned long long) n);

        ll ans = 1;

        for (int len = 1; len < m; len++) {
            ans += (1LL << ((len - 1) / 2));
        }

        int half = (m + 1) / 2;

        for (int i = 1; i < half; i++) {

            int b = m - 1 - i;
            if ((n >> b) & 1) {
                int rem = half - 1 - i;
                ans += (1LL << rem);
            }
        }

        ll left = n >> (m - half);
        ll mask = 0;
        for (int i = 0; i < m; i++) {
            int r = m - 1 - i;
            if (i <= r) {
                int bit = (left >> (half - 1 - i)) & 1;
                if (bit)
                    mask |= (1LL << r);
                if (bit)
                    mask |= (1LL << i);
            }
        }

        if (mask <= n && mask != 0)
            ans++;

        return ans;
    }
};
