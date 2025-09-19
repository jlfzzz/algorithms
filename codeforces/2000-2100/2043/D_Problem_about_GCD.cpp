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
    int l, r, G;
    cin >> l >> r >> G;

    auto check = [&](int x) {
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0)
                return false;
        }
        return true;
    };

    int lo = (l + G - 1) / G;
    int hi = r / G;

    for (int len = hi - lo + 1; len >= 1; len--) {
        for (int i = lo; i + len - 1 <= hi; i++) {
            if (gcd(i, i + len - 1) == 1) {
                cout << i * G << ' ' << (i + len - 1) * G << '\n';
                return;
            }
        }
    }

    cout << "-1 -1" << '\n';
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
