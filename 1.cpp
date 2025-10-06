#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int64 MOD = 1000000007;

int64 modpow(int64 a, int64 e) {
    int64 r = 1;
    while (e) {
        if (e & 1)
            r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, b;
    if (!(cin >> n >> k >> b))
        return 0;
    vector<int> c(k);
    for (int i = 0; i < k; ++i)
        cin >> c[i];

    int m = n - b; // 彩色总数
    int R = min(b, m); // 我们只需计算 r = 0..R

    // 预计算阶乘与逆阶乘到 m
    vector<int64> fact(m + 1), invfact(m + 1);
    fact[0] = 1;
    for (int i = 1; i <= m; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    if (m >= 0) {
        invfact[m] = modpow(fact[m], MOD - 2);
        for (int i = m; i >= 1; --i)
            invfact[i - 1] = invfact[i] * i % MOD;
    }

    // dp[r] 对应 AR(y) 的 y^r 的系数（初始 dp[0] = 1）
    vector<int64> dp(R + 1);
    dp[0] = 1;

    for (int idx = 0; idx < k; ++idx) {
        int ci = c[idx];
        int lim = min(ci, R);
        vector<int64> ndp(R + 1, 0);
        for (int cur_r = 0; cur_r <= R; ++cur_r) {
            if (dp[cur_r] == 0)
                continue;
            int max_t = min(lim, R - cur_r);
            for (int t = 0; t <= max_t; ++t) {
                // p_i[t] = 1 / (ci - t)!  => invfact[ci - t]
                ndp[cur_r + t] = (ndp[cur_r + t] + dp[cur_r] * invfact[ci - t]) % MOD;
            }
        }
        dp.swap(ndp);
    }

    int64 ans = 0;
    for (int r = 0; r <= R; ++r) {
        int s = m - r; // 对应的最终栈长度
        if (s < 0)
            continue;
        int64 add = dp[r] * fact[s] % MOD;
        ans = (ans + add) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
