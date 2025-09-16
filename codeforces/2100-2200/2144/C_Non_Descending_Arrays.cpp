#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    // map<pii, int> memo;
    // auto dfs = [&](this auto &&dfs, int i, int mn) -> int {
    //     if (i == n) {
    //         return 1;
    //     }

    //     if (memo.contains({i, mn})) {
    //         return memo[{i, mn}];
    //     }

    //     int x = a[i];
    //     int y = b[i];
    //     int res = 0;
    //     if (x >= mn && y >= mn) {
    //         res = (dfs(i + 1, x) + dfs(i + 1, y)) % MOD;
    //     } else if (x >= mn) {
    //         res = dfs(i + 1, x);
    //     } else if (y >= mn) {
    //         res = dfs(i + 1, y);
    //     }

    //     memo[{i, mn}] = res;
    //     return res;
    // };

    // int ans = dfs(0, -1);

    array<int, 2> dp = {1, 1};
    for (int i = 1; i < n; i++) {
        array<int, 2> ndp = {0, 0};
        int a0 = a[i - 1], b0 = b[i - 1];
        int a1 = a[i], b1 = b[i];
        if (a0 <= a1 && b0 <= b1) {
            ndp[0] = (ndp[0] + dp[0]) % MOD;
        }
        if (b0 <= a1 && a0 <= b1) {
            ndp[0] = (ndp[0] + dp[1]) % MOD;
            ndp[1] = (ndp[1] + dp[0]) % MOD;
        }
        if (b0 <= b1 && a0 <= a1) {
            ndp[1] = (ndp[1] + dp[1]) % MOD;
        }
        dp = ndp;
    }
    int ans = (dp[0] + dp[1]) % MOD;
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
