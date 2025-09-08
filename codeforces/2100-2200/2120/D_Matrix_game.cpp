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

const int N = 500'005;

vector<ll> fac(N), ifac(N);

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

void init() {
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    ifac[N - 1] = qpow(fac[N - 1], MOD - 2);
    for (int i = N - 2; i >= 1; --i)
        ifac[i] = ifac[i + 1] * (i + 1) % MOD;
}

ll C(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

ll C_large(long long n, int a) {
    if (a < 0)
        return 0;
    if (n < a)
        return 0;
    ll res = 1;
    for (int i = 0; i < a; ++i) {
        ll term = ((n - i) % MOD + MOD) % MOD;
        res = (res * term) % MOD;
    }
    res = res * ifac[a] % MOD;
    return res;
}
void solve() {
    int a, b, k;
    cin >> a >> b >> k;

    int n = (a - 1) * k + 1;
    int m = (((b - 1) * k % MOD) * C_large(n, a) % MOD) + 1ll;
    cout << n % MOD << ' ' << m % MOD << '\n';
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
