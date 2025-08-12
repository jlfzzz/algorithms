#include <iostream>
#include <numeric>
#include <vector>


// 使用 long long 以免 n, m 溢出
using ll = long long;

// 1. 快速幂
// 计算 (base^exp) % mod
ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (__int128) res * base % mod;
        base = (__int128) base * base % mod;
        exp /= 2;
    }
    return res;
}

// 2. 扩展欧几里得算法
// 求解 ax + by = gcd(a, b)，并返回 gcd(a, b)
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = ex_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

// 3. 模逆元 (基于扩展欧几里得)
// 计算 a 在模 m 下的逆元，要求 gcd(a, m) == 1
ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll d = ex_gcd(a, m, x, y);
    if (d != 1)
        return -1; // 逆元不存在
    return (x % m + m) % m;
}

// 4. 扩展卢卡斯定理的核心部分
// 计算 n! 中质因子 p 的数量 (勒让德公式)
ll count_p_in_factorial(ll n, ll p) {
    if (n < p)
        return 0;
    return n / p + count_p_in_factorial(n / p, p);
}

// 计算 n! mod p^k，但剔除所有 p 的因子
ll factorial_mod_pk(ll n, ll p, ll pk) {
    if (n == 0)
        return 1;
    ll res = 1;
    // 计算 1 到 pk 中与 p 互质的数的乘积
    if (n >= pk) {
        for (ll i = 1; i <= pk; ++i) {
            if (i % p != 0) {
                res = (__int128) res * i % pk;
            }
        }
        // 这个乘积会重复 (n/pk) 次
        res = power(res, n / pk, pk);
    }

    // 计算剩余部分 n % pk 的乘积
    for (ll i = 1; i <= n % pk; ++i) {
        if (i % p != 0) {
            res = (__int128) res * i % pk;
        }
    }
    // 递归处理 n/p 的阶乘
    res = (__int128) res * factorial_mod_pk(n / p, p, pk) % pk;
    return res;
}

// 计算 C(n, m) mod p^k
ll combination_mod_pk(ll n, ll m, ll p, ll pk) {
    if (m < 0 || m > n)
        return 0;

    // 1. 计算 C(n, m) 中质因子 p 的最终幂次
    ll power_of_p = count_p_in_factorial(n, p) - count_p_in_factorial(m, p) - count_p_in_factorial(n - m, p);

    // 2. 计算剔除因子p后的阶乘部分
    ll res = factorial_mod_pk(n, p, pk);
    res = (__int128) res * mod_inverse(factorial_mod_pk(m, p, pk), pk) % pk;
    res = (__int128) res * mod_inverse(factorial_mod_pk(n - m, p, pk), pk) % pk;

    // 3. 将之前剔除的因子 p 的幂次乘回来
    res = (__int128) res * power(p, power_of_p, pk) % pk;
    return res;
}

// 5. 中国剩余定理 (CRT) - 两两合并
ll crt(ll a1, ll m1, ll a2, ll m2) {
    ll M = m1 * m2;
    ll t = mod_inverse(m1, m2);
    ll x = (a2 - a1 % m2 + m2) % m2;
    x = (__int128) x * t % m2;
    return (a1 + (__int128) x * m1) % M;
}

// 6. 扩展卢卡斯定理主函数
ll ex_lucas(ll n, ll m, ll p_mod) {
    if (m < 0 || m > n)
        return 0;
    if (p_mod == 1)
        return 0;

    ll temp_M = p_mod;

    // CRT 初始化
    ll current_rem = 0;
    ll current_mod = 1;

    // 分解模数 p_mod
    for (ll i = 2; i * i <= temp_M; ++i) {
        if (temp_M % i == 0) {
            ll pk = 1;
            while (temp_M % i == 0) {
                pk *= i;
                temp_M /= i;
            }
            // 对每个质数幂求解，并用CRT合并
            ll rem = combination_mod_pk(n, m, i, pk);
            current_rem = crt(current_rem, current_mod, rem, pk);
            current_mod *= pk;
        }
    }
    if (temp_M > 1) { // 剩余一个大的质因子
        ll pk = temp_M;
        ll p = temp_M;
        ll rem = combination_mod_pk(n, m, p, pk);
        current_rem = crt(current_rem, current_mod, rem, pk);
        current_mod *= pk;
    }

    return current_rem;
}

// 主函数，处理输入输出
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, m, p;
    std::cin >> n >> m >> p;
    std::cout << ex_lucas(n, m, p) << std::endl;

    return 0;
}
