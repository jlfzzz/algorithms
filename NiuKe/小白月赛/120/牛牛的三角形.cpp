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

const int N = 1500;

vector<ll> fac(N + 1), ifac(N + 1);
int M;
static vector<vector<int>> CNT;

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
    for (int i = 1; i <= N; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    ifac[N] = qpow(fac[N], MOD - 2);
    for (int i = N - 1; i >= 1; --i)
        ifac[i] = ifac[i + 1] * (i + 1) % MOD;

    int f1 = 1, f2 = 2;
    M = 2;
    while (true) {
        int f3 = f1 + f2;
        M++;
        if (f3 > N) {
            break;
        }
        f1 = f2, f2 = f3;
    }
}

ll C(int n, int k) {
    if (k < 0 || k > n)
        return 0;
    return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}

void build() {
    CNT.assign(M + 1, vector<int>(N + 1, 0));

    vector<vector<int>> dp_prev(N + 1, vector<int>(N + 1, 0));
    for (int j = 1; j <= N; ++j)
        for (int i = j + 1; i <= N; ++i)
            dp_prev[j][i] = 1; // len=2

    {
        vector<int> endSum(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int s = 0;
            for (int j = 1; j < i; ++j) {
                s += dp_prev[j][i];
                if (s >= MOD)
                    s -= MOD;
            }
            endSum[i] = s;
        }
        for (int k = 1; k <= N; ++k) {
            int x = (k ? CNT[2][k - 1] : 0) + endSum[k];
            if (x >= MOD)
                x -= MOD;
            CNT[2][k] = x;
        }
    }

    vector<vector<int>> dp_cur(N + 1, vector<int>(N + 1, 0));
    vector<int> pre_x(N + 1, 0);

    for (int len = 3; len <= M; ++len) {
        for (int j = 2; j <= N; ++j) {
            pre_x[0] = 0;
            for (int x = 1; x <= j - 1; ++x) {
                int v = pre_x[x - 1] + dp_prev[x][j];
                if (v >= MOD)
                    v -= MOD;
                pre_x[x] = v;
            }
            for (int i = j + 1; i <= N; ++i) {
                int l = (int) min<int>(j - 1, i - j);
                if (l >= 1)
                    dp_cur[j][i] = pre_x[l];
            }
        }
        vector<int> endSum(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            int s = 0;
            for (int j = 1; j < i; ++j) {
                s += dp_cur[j][i];
                if (s >= MOD)
                    s -= MOD;
            }
            endSum[i] = s;
        }
        for (int k = 1; k <= N; ++k) {
            int x = (k ? CNT[len][k - 1] : 0) + endSum[k];
            if (x >= MOD)
                x -= MOD;
            CNT[len][k] = x;
        }
        for (int j = 1; j <= N; ++j)
            for (int i = j + 1; i <= N; ++i)
                dp_prev[j][i] = dp_cur[j][i], dp_cur[j][i] = 0;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    if (m < 3) {
        cout << 0 << '\n';
        return;
    }
    if (m >= M) {
        cout << 1 << '\n';
        return;
    }

    ll bad = CNT[m][n];
    ll sum = C(n, m);
    ll ans = (1 - bad % MOD * qpow(sum, MOD - 2) % MOD + MOD) % MOD;
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
