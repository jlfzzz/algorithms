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
constexpr double EPS = 1e-9;

ll iceil_sqrt128(__int128 x) {
    if (x < 0)
        return -1;
    auto dx = (long double) x;
    ll r = (ll) floor(sqrtl(dx));
    while ((__int128) r * r < x)
        ++r;
    return r;
}
void solve() {
    int n;
    cin >> n;

    int ans = iceil_sqrt128(n) - 1;
    cout << ans << '\n';
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
