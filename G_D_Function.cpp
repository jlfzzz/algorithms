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
    int l, r, k;
    cin >> l >> r >> k;
    if (k >= 10) {
        cout << 0 << '\n';
        return;
    }

    auto q_pow = [&](int base, int power) -> int {
        int res = 1;
        while (power) {
            if (power & 1) {
                res = res * base % MOD;
            }
            base = base * base % MOD;
            power >>= 1;
        }
        return res;
    };

    int contri = 9 / k + 1;
    int ans = (q_pow(2, l) * ((1 - q_pow(2, r - l) + MOD) % MOD) % MOD * (MOD - 1)) % MOD;


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
