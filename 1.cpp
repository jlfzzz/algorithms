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

const int N = 1505;

vector<ll> fac(N), ifac(N);
vector<vector<ll>> pref_no_tri;
vector<ll> fib;
int mmaxi;

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

void build() {
    fib.assign(N * 2, 0);
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i < (int) fib.size(); ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
    mmaxi = 2;
    while (mmaxi + 1 < (int) fib.size() && fib[mmaxi + 1] <= 1500)
        ++mmaxi;
    pref_no_tri.assign(mmaxi + 1, vector<ll>(N, 0));
    for (int m = 3; m <= mmaxi; ++m) {
        vector<int> w(m);
        for (int i = 0; i < m; ++i)
            w[i] = (int) fib[m - i];
        vector<ll> dp(N, 0);
        dp[0] = 1;
        for (int i = 0; i < m; ++i) {
            int ww = w[i];
            for (int s = ww; s < N; ++s) {
                dp[s] += dp[s - ww];
                if (dp[s] >= MOD)
                    dp[s] -= MOD;
            }
        }
        pref_no_tri[m][0] = dp[0];
        for (int s = 1; s < N; ++s) {
            pref_no_tri[m][s] = pref_no_tri[m][s - 1] + dp[s];
            if (pref_no_tri[m][s] >= MOD)
                pref_no_tri[m][s] -= MOD;
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    if (m < 3) {
        cout << 0 << '\n';
        return;
    }

    int total = C(n, m);
    if (total == 0) {
        cout << 0 << '\n';
        return;
    }

    ll no_tri = 0;
    if (m <= mmaxi) {
        int need = (int) fib[m + 1];
        if (n >= need) {
            int L = n - need;
            if (L >= N)
                L = N - 1;
            no_tri = pref_no_tri[m][L];
        }
    }

    ll ans = ((total - no_tri) % MOD + MOD) % MOD;
    ans = ans * qpow(total, MOD - 2) % MOD;
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    build();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
