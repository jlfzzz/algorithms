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

void init() {}

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

ll f(int R) {
    if (R <= 0)
        return 0;
    ll t = 0;
    for (int i = 1; i < R; ++i) {
        __int128 rem = (__int128) R * R - 1 - (__int128) i * i;
        if (rem < 0)
            continue;
        ll h = isqrt128(rem);
        t += h;
    }
    return 1 + 4LL * (R - 1) + 4LL * t;
}

void solve() {
    int r;
    cin >> r;
    cout << (f(r + 1) - f(r)) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
