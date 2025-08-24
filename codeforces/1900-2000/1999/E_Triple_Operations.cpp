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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

int pow3[30];

void init() {
    pow3[0] = 1;
    for (int i = 1; i < 30; i++) {
        pow3[i] = pow3[i - 1] * 3;
    }
}

void solve() {
    int l, r;
    cin >> l >> r;

    int ans = 0;
    int t = l + 1;
    int tt = l;
    while (tt) {
        tt /= 3;
        t *= 3;
        ans++;
    }

    int i = l + 2;
    int j = ranges::upper_bound(pow3, i) - pow3;

    ans += (min(pow3[j] - 1, r) - i + 1) * j;
    i = pow3[j];
    for (; i <= r; i *= 3) {
        j = ranges::upper_bound(pow3, i) - pow3;
        ans += (min(pow3[j] - 1, r) - i + 1) * j;
    }

    ans += ranges::upper_bound(pow3, t) - pow3;
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
