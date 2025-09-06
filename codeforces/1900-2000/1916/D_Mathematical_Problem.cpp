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
    int n;
    cin >> n;

    if (n == 1) {
        cout << 1 << "\n";
        return;
    }

    cout << 196 << string(n - 3, '0') << "\n";
    for (int i = 0; i < n / 2; i++) {
        cout << 1 << string(i, '0') << 6 << string(i, '0') << 9 << string(n - 3 - 2 * i, '0') << "\n";
        cout << 9 << string(i, '0') << 6 << string(i, '0') << 1 << string(n - 3 - 2 * i, '0') << "\n";
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
