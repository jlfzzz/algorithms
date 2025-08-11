#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

const int N = 500'005;

vector<ll> fac(N), ifac(N);

// 快速幂
ll qpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 预处理阶乘和逆元
void init() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    ifac[N - 1] = qpow(fac[N - 1], MOD - 2);
    for (int i = N - 2; i >= 1; --i)
        ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}

// 组合数 C(n, k)
ll C(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void solve() {
    vector<int> cnt(27);
    For(i, 26) { cin >> cnt[i + 1]; }

    int sm = accumulate(cnt.begin(), cnt.end(), 0ll);

    // 奇偶位置数量
    int k = sm / 2;
    vector<int> dp(k + 1);
    dp[0] = 1;

    for (int i = 1; i <= 26; i++) {
        int x = cnt[i];
        if (x == 0)
            continue;

        for (int j = k; j >= x; j--) {
            dp[j] = (dp[j] + dp[j - x]) % MOD;
        }
    }

    int odd = sm - k;
    int ans = dp[k] * fac[k] % MOD * fac[odd] % MOD;
    for (int i = 1; i <= 26; i++) {
        ans = ans * ifac[cnt[i]] % MOD;
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
