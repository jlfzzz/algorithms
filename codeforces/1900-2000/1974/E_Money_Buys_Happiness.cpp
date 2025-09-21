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
    int m, x;
    cin >> m >> x;

    vector<pii> v(m);
    int total = 0;
    For(i, m) {
        int c, h;
        cin >> c >> h;
        total += h;
        v[i] = {c, h};
    }

    vector<int> dp(total + 1, inf);
    dp[0] = 0;

    for (int j = 0; j < m; j++) {
        auto &[c, h] = v[j];
        for (int i = total; i >= 0; i--) {
            if (i - h >= 0 && dp[i - h] != inf) {
                int cost = dp[i - h];
                int have = j * x;
                if (have - cost >= c) {
                    dp[i] = min(dp[i], dp[i - h] + c);
                }
            }
        }
    }

    for (int i = total; i >= 0; i--) {
        if (dp[i] != inf) {
            cout << i << '\n';
            return;
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
