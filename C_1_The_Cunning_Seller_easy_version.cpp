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

int pow3[27];
int cost[27];

void init() {
    pow3[0] = 1;
    for (int i = 1; i < 27; i++) {
        pow3[i] = pow3[i - 1] * 3;
    }

    cost[0] = 3;
    for (int i = 1; i < 27; i++) {
        cost[i] = pow3[i + 1] + i * pow3[i - 1];
    }
}

void solve() {
    int n;
    cin >> n;

    int ans = 0;

    for (int i = 0; i < 27 && n > 0; i++) {
        int digit = n % 3;
        if (digit > 0) {
            ans += digit * cost[i];
        }
        n /= 3;
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
