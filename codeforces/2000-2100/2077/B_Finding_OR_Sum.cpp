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
    int a = 0, b = 0;
    for (int i = 1; i < 30; i += 2)
        a += 1 << i;
    for (int i = 0; i < 30; i += 2)
        b += 1 << i;

    cout << a << endl;
    int res;
    cin >> res;

    int t = res - 2 * a;
    int x = 0, y = 0;
    for (int i = 0; i < 30; i += 2) {
        int bit = 1 << i;
        int next = 1 << (i + 1);
        if (t & bit) {
            x |= bit;
        } else if (t & next) {
            x |= bit;
            y |= bit;
        }
    }

    cout << b << endl;
    cin >> res;
    t = res - 2 * b;
    for (int i = 1; i < 30; i += 2) {
        int bit = 1 << i;
        int next = 1 << (i + 1);
        if (t & bit) {
            x |= bit;
        } else if (t & next) {
            x |= bit;
            y |= bit;
        }
    }
    cout << "!" << endl;
    int m;
    cin >> m;

    int ans = (m | x) + (m | y);

    cout << ans << endl;
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
