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
    vector<int> a(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    int N = (mx == 0 ? 1 : 64 - __builtin_clzll(mx));
    vector<int> dp(1 << N, (1ll << 60) - 1);

    for (int x: a) {
        dp[x] = x;
    }

    // 父集更新子集
    for (int i = 0; i < N; i++) {
        for (int mask = 0; mask < (1 << N); mask++) {
            if (mask & (1 << i)) {
                dp[mask ^ (1 << i)] &= dp[mask];
            }
        }
    }

    int ans = 0;
    while (true) {
        if (ans == 0) {
            ans++;
            continue;
        }
        if (ans >= (1 << N)) {
            cout << (1 << N) << "\n";
            return;
        }
        if (dp[ans] != ans) {
            cout << ans << "\n";
            return;
        }
        ans++;
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
