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
    int n, m;
    cin >> n >> m;
    int k;
    cin >> k;
    vector<int> c(n + 1);
    For(i, k) {
        int t;
        cin >> t;
        c[t] = 1;
    }

    // pos 从右往左的
    auto remove = [&](int mask, int pos) -> int {
        int right = mask & ((1 << (pos - 1)) - 1);
        int left = mask >> pos << (pos - 1);
        return left | right;
    };
    vector<unsigned char> prev0(2), prev1(2);
    prev0[1] = 1;
    prev1[1] = 1;
    for (int i = 2; i <= n; i++) {
        int u = 1 << i;
        vector<unsigned char> cur0(u), cur1(u);
        for (int mask = 0; mask < u; mask++) {
            bool f0 = false, f1 = true;
            for (int j = 1; j <= i; j++) {
                if (!c[j])
                    continue;
                int last_mask = remove(mask, j);
                f0 |= prev1[last_mask];
                f1 &= prev0[last_mask];
            }
            cur0[mask] = f0;
            cur1[mask] = f1;
        }
        prev0.swap(cur0);
        prev1.swap(cur1);
    }
    vector<int> cnt(n + 1);
    for (int mask = 0; mask < (1 << n); mask++) {
        if (prev0[mask]) {
            cnt[__builtin_popcountll(mask)] += 1;
        }
    }

    if (m == 1) {
        cout << 1 << '\n';
        return;
    }

    // 预计算 m^i
    vector<int> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
        pw[i] = pw[i - 1] * (m % MOD) % MOD;

    auto mod_pow = [&](int x, int y) {
        int res = 1 % MOD;
        int base = x % MOD;
        while (y > 0) {
            if (y & 1)
                res = res * base % MOD;
            base = base * base % MOD;
            y >>= 1;
        }
        return res;
    };

    int ans = pw[n]; // 所有方案数
    for (int i = 1; i < m; i++) {
        int manji = i, veci = m - i;
        for (int j = 0; j <= n; j++) {
            if (!cnt[j])
                continue;
            ans = (ans + cnt[j] % MOD * mod_pow(manji, n - j) % MOD * mod_pow(veci, j) % MOD) % MOD;
        }
    }

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
