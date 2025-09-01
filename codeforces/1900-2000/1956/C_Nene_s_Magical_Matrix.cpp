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
    ll n;
    cin >> n;

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        ans += i * (i * 2 - 1);
    }

    cout << ans << " " << n * 2 << "\n";

    for (ll i = n; i >= 1; i--) {
        cout << "1 " << i << " ";
        for (ll j = 1; j <= n; j++)
            cout << j << " ";
        cout << "\n";

        cout << "2 " << i << " ";
        for (ll j = 1; j <= n; j++)
            cout << j << " ";
        cout << "\n";
    }
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
