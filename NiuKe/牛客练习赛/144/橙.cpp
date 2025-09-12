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
    int l, r;
    cin >> l >> r;

    auto f = [&](int x) -> int {
        int res = 0;
        while (x) {
            res += x % 10;
            x /= 10;
        }
        return res;
    };

    bool t = false;
    while (l <= r) {
        int s = f(l);
        if (s % 13 == 0) {
            if (!t) {
                t = true;
            } else {
                cout << l << '\n';
                return;
            }
        }
        l++;
    }

    cout << -1 << '\n';
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
