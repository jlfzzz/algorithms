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
    long long k, x, a;
    cin >> k >> x >> a;
    long long pre = 0;

    for (int i = 1; i <= x; i++) {
        long long cur = pre / (k - 1) + 1;
        if (cur > a) {
            cout << "NO\n";
            return;
        }
        a -= cur;
        pre += cur;
    }

    if (a * (k - 1) <= pre) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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
