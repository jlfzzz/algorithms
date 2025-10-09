#include <bits/stdc++.h>
using namespace std;

// 题意摘要：非黑色共有 k 种，计数 c_i，黑色 b 个，总 n。把花瓣依次入栈；
// 遇到黑色：若栈非空则弹掉栈顶（相当于消去一个彩色），否则什么也不弹。
// 问最终可能的栈序列个数。
// 推导：最终长度 L ∈ [max(m-b,0), m]，其中 m = sum c_i。
// 对固定 L，答案为 L! * [x^L] Π_i Σ_{t=0}^{c_i} x^t / t!。
// 为了只求接近总度数 m 的最高 b+1 个系数，做“总度数反转”：
// 令 P(x) = Π_i Σ_{t=0}^{c_i} x^t / t!，总度数 m；R(y) = y^m P(1/y) = Π_i Q_i(y)。
// 则 [x^{m-t}]P(x) = [y^t]R(y)。
// 而 Q_i(y) = Σ_{t=0}^{c_i} y^{c_i - t} / t! = Σ_{r=0}^{c_i} y^r / (c_i - r)!
// 只需 R(y) 的 0..b 次项，因此每个 Q_i 只取前 min(b, c_i)+1 项即可，
// 用长度 b+1 的 DP 做多项式卷积，复杂度 O(k * b^2)。

static const int MOD = 1000000007;

long long modPow(long long a, long long e) {
    long long r = 1 % MOD;
    while (e > 0) {
        if (e & 1)
            r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int k, b;
    if (!(cin >> n >> k >> b))
        return 0;
    vector<int> c(k);
    long long m = 0;
    for (int i = 0; i < k; i++) {
        cin >> c[i];
        m += c[i];
    }

    // 预处理阶乘与逆阶乘到 m（m ≤ 1e5）
    vector<long long> fact(m + 1), invfact(m + 1);
    fact[0] = 1;
    for (long long i = 1; i <= m; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[m] = modPow(fact[m], MOD - 2);
    for (long long i = m - 1; i >= 0; i--)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;

    int B = (int) min<long long>(b, m); // 只需要 0..B 的 R(y) 系数

    // dp[i] 代表被黑色抵消/删除了i个
    // dp[0]就是一个没删。所以最后求答案的时候，L=m-t,t=0时候就是L=m，所以再乘L的阶乘
    // 内层的两个for
    // r代表当前或者说最新的dp，代表已经选了r个去被黑色删除
    // 枚举t，t<=min(ci,B)代表当前选t个去被黑色的删
    // 所以是当前选了t被删，剩下的排列数也就是系数就是ci-t的阶乘，除掉这个玩意的逆元就是系数转移
    // 所以最后答案循环，对于dp[i]代表选了i个被黑色删，剩下的所有其它的就是m - t，就是再乘这个的阶乘就是答案

    vector<long long> dp(B + 1, 0), ndp(B + 1, 0);
    dp[0] = 1; // R(y) 初始为 1
    int curMax = 0; // 当前已知的最高次数（≤ B）

    // 关键转移循环
    for (int i = 0; i < k; i++) {
        int ci = c[i];
        int take = min(B, ci); // Q_i 只需 0..take 次项
        fill(ndp.begin(), ndp.end(), 0);
        for (int r = 0; r <= curMax; r++)
            if (dp[r]) {
                for (int t = 0; t <= take && r + t <= B; t++) {
                    // Q_i 的 y^t 系数 = 1 / (ci - t)!
                    long long coef = invfact[ci - t];
                    ndp[r + t] = (ndp[r + t] + dp[r] * coef) % MOD;
                }
            }
        dp.swap(ndp);
        curMax = min(B, curMax + take);
    }

    long long ans = 0;
    // t = m - L，L 从 max(m-b,0) 到 m，对应 t 从 0 到 B
    for (int t = 0; t <= B; t++) {
        long long L = m - t;
        // 保护：若 L < 0（理论不会发生）则跳过
        if (L < 0)
            continue;
        ans = (ans + fact[L] * dp[t]) % MOD;
    }

    cout << ans % MOD << "\n";
    return 0;
}
