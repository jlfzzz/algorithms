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
    int n, m;
    cin >> n >> m;
    int ans = 1;

    auto q_pow = [&](int base, int power) {
        int res = 1;
        while (power) {
            if (power & 1) {
                res = res * base % MOD;
            }
            base = base * base % MOD;
            power >>= 1;
        }
        return res;
    };

    map<int, vector<pii>> cnt;
    For(i, n) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        int p1 = p * q_pow(q, MOD - 2) % MOD;
        int p2 = (1 - p1 + MOD) % MOD;
        ans = ans * p2 % MOD;
        cnt[r].emplace_back(l, p1 * q_pow(p2, MOD - 2) % MOD);
    }

    vector<int> dp(m + 1);
    dp[0] = 1;
    for (int i = 1; i <= m; i++) {
        if (cnt.contains(i)) {
            // cout << i << endl;

            for (auto &[l, p]: cnt[i]) {
                dp[i] = (dp[i] + (p * dp[l - 1] % MOD)) % MOD;
            }
        }
    }

    cout << dp[m] * ans % MOD << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
