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
    int n, k;
    cin >> n >> k;

    int ans = -1;
    if (k == 1) {
        ans = n % MOD;
    } else {
        int a1 = 1, a2 = 1, a3;
        for (int i = 3; true; i++) {
            a3 = (a1 + a2) % k;
            if (!a3) {
                ans = i;
                break;
            }
            a1 = a2, a2 = a3;
        }
        ans = n % MOD * ans % MOD;
    }
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
