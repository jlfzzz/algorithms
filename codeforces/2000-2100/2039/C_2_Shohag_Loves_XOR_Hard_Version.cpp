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

void solve() {
    int x, m;
    cin >> x >> m;

    int maxp = m - m % x;
    int ans = maxp / x - (x < maxp);

    if (1 <= ((maxp ^ x)) && ((maxp ^ x)) <= m)
        ans++;
    if (1 <= (((maxp + x) ^ x)) && (((maxp + x) ^ x)) <= m)
        ans++;

    for (int y = 1; y <= min(x, m); y++)
        if (((x ^ y) % y) == 0 && (((x ^ y) % x) != 0 && x != y))
            ans++;
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
