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
    int n, q;
    cin >> n >> q;

    for (int i = 1; i < n; i++) {
        cout << i << ' ' << i + 1 << '\n';
    }

    bool f = true;
    int t = n - 1;

    while (q--) {
        int d;
        cin >> d;

        auto reply = [&](int x, int y, int z) { cout << x << ' ' << y << ' ' << z << '\n'; };

        if (d == n - 1) {
            if (f) {
                reply(-1, -1, -1);
            } else {
                reply(n, t, n - 1);
                t = n - 1;
                f = true;
            }
        } else {
            if (t == d) {
                reply(-1, -1, -1);
                continue;
            }

            if (f) {
                reply(n, n - 1, d);

                f = false;
                t = d;
            } else {
                reply(n, t, d);

                t = d;
            }
        }
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
