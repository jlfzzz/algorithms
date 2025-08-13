#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
const ll MOD2 = 4611686018427387847;
constexpr int inf = 100'000'005;


class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        int ans = 0;

        while (tx != sx or ty != sy) {
            if (tx < ty) {
                swap(tx, ty);
                swap(sx, sy);
            }

            if (tx < sx or ty < sy) {
                return -1;
            }

            if (tx == ty) {
                if (sx == 0) {
                    tx = 0;
                    ans++;
                    continue;
                } else if (sy == 0) {
                    ty = 0;
                    ans++;
                    continue;
                }
            }

            if (tx > 2 * ty) {
                if (tx & 1) {
                    return -1;
                }
                tx /= 2;
            } else {
                tx -= ty;
            }
            ans++;
        }
        return ans;
    }
};
