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
    int a, b;
    cin >> a >> b;
    if ((a & 1) == 0) {
        if (b & 1) {
            cout << -1 << '\n';
        } else {
            cout << a * (b / 2) + 2 << '\n';
        }
        return;
    }

    if (b & 1) {
        cout << a * b + 1 << '\n';
        return;
    }

    int bb = b;
    int t = 0;
    while ((bb & 1) == 0) {
        t++;
        bb >>= 1;
    }
    if (t == 1) {
        cout << -1 << '\n';
    } else {
        cout << a * (b / 2) + 2 << '\n';
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
