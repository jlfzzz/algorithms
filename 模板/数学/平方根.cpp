#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

ll isqrt128(__int128 x) {
    if (x < 0)
        return -1;
    auto dx = (long double) x;
    ll r = (ll) floor(sqrtl(dx));
    while ((__int128) (r + 1) * (r + 1) <= x)
        ++r;
    while ((__int128) r * r > x)
        --r;
    return r;
}
