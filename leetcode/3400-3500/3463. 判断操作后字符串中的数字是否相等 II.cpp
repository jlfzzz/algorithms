#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

// 使用 long long 避免溢出
using ll = long long;

// 1. 扩展欧几里得算法
// 求解 ax + by = gcd(a, b)，并返回 gcd(a, b)
// x 和 y 将通过引用传出
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

// 2. 模逆元 (基于扩展欧几里得)
// 计算 a 在模 m 下的逆元，要求 gcd(a, m) == 1
ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll d = ex_gcd(a, m, x, y);
    if (d != 1) {
        // 如果 a 和 m 不互质，则逆元不存在
        return -1;
    }
    return (x % m + m) % m; // 保证结果是正数
}


// 3. 快速幂
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

// 4. 扩展卢卡斯定理的核心部分
// 计算 n! mod p^k，但剔除所有 p 的因子
ll factorial_mod_pk(ll n, ll p, ll pk) {
    if (n == 0)
        return 1;
    ll res = 1;
    // 计算 1 到 pk 中与 p 互质的数的乘积
    for (ll i = 1; i <= pk; ++i) {
        if (i % p != 0) {
            res = (__int128) res * i % pk;
        }
    }
    // 这个乘积会重复 (n/pk) 次
    res = power(res, n / pk, pk);

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

// 计算 n! 中质因子 p 的数量 (勒让德公式)
ll count_p_in_factorial(ll n, ll p) {
    ll count = 0;
    while (n > 0) {
        count += n / p;
        n /= p;
    }
    return count;
}

// 计算 C(n, m) mod p^k
ll combination_mod_pk(ll n, ll m, ll p, ll pk) {
    if (m < 0 || m > n)
        return 0;

    // 1. 计算 n!, m!, (n-m)! 中质因子 p 的数量
    ll count_p_n = count_p_in_factorial(n, p);
    ll count_p_m = count_p_in_factorial(m, p);
    ll count_p_nm = count_p_in_factorial(n - m, p);

    // 2. 计算 C(n, m) 中质因子 p 的最终幂次
    ll power_of_p = count_p_n - count_p_m - count_p_nm;

    // 3. 计算剔除因子p后的阶乘部分
    ll res = factorial_mod_pk(n, p, pk);
    res = (__int128) res * mod_inverse(factorial_mod_pk(m, p, pk), pk) % pk;
    res = (__int128) res * mod_inverse(factorial_mod_pk(n - m, p, pk), pk) % pk;

    // 4. 将之前剔除的因子 p 的幂次乘回来
    res = (__int128) res * power(p, power_of_p, pk) % pk;
    return res;
}

// 5. 中国剩余定理 (CRT)
// 求解 x ≡ a (mod m) 的方程组
// 这里只实现了两两合并，可以循环使用
ll crt(ll a1, ll m1, ll a2, ll m2) {
    ll M = m1 * m2;
    ll t1 = M / m1, t2 = M / m2;
    ll inv1 = mod_inverse(t1, m1);
    ll inv2 = mod_inverse(t2, m2);
    ll res = ((__int128) a1 * t1 % M * inv1 % M + (__int128) a2 * t2 % M * inv2 % M) % M;
    return res;
}

// 6. 扩展卢卡斯定理主函数
ll ex_lucas(ll n, ll m, ll M) {
    if (m < 0 || m > n)
        return 0;
    if (M == 1)
        return 0;

    ll temp_M = M;
    std::vector<ll> prime_powers;

    // 分解模数 M
    for (ll i = 2; i * i <= temp_M; ++i) {
        if (temp_M % i == 0) {
            ll pk = 1;
            while (temp_M % i == 0) {
                pk *= i;
                temp_M /= i;
            }
            prime_powers.push_back(pk);
        }
    }
    if (temp_M > 1) {
        prime_powers.push_back(temp_M);
    }

    // CRT 初始化
    ll current_rem = 0;
    ll current_mod = 1;

    // 对每个质数幂求解，并用CRT合并
    for (ll pk: prime_powers) {
        ll p = pk;
        if (p % 2 == 0)
            p = 2;
        else {
            for (ll i = 3; i * i <= p; i += 2) {
                if (p % i == 0) {
                    p = i;
                    break;
                }
            }
        }

        ll rem = combination_mod_pk(n, m, p, pk);
        current_rem = crt(current_rem, current_mod, rem, pk);
        current_mod *= pk;
    }

    return current_rem;
}

class Solution {
public:
    bool hasSameDigits(string s) {
        int n = s.size();

        ll ans1 = 0;
        for (int i = 0; i < n - 1; i++) {
            ans1 = (ans1 + ex_lucas(n - 2, i, 10) * (s[i] - '0')) % 10;
        }
        ll ans2 = 0;
        for (int i = 1; i < n; i++) {
            ans2 = (ans2 + ex_lucas(n - 2, i - 1, 10) * (s[i] - '0')) % 10;
        }
        ans1 %= 10, ans2 %= 10;
        return ans1 == ans2;
    }
};






// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;
// using pii = pair<int, int>;
// using pll = pair<ll, ll>;
// #define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
// constexpr int MOD = int(1e9 + 7);
// #define i128 __int128_t
// #define ull unsigned long long
// const ll MOD2 = 4611686018427387847;
// constexpr int inf = 100'000'005;


// const int MOD = 10;
// const int MX = 100'000;
// array<int, MX + 1> f, inv_f, p2, p5;

// int qpow(int x, int n) {
//     int res = 1;
//     while (n > 0) {
//         if (n % 2 > 0) {
//             res = res * x % MOD;
//         }
//         x = x * x % MOD;
//         n /= 2;
//     }
//     return res;
// }

// auto init = []() {
//     f[0] = 1;
//     for (int i = 1; i <= MX; i++) {
//         int x = i;
//         // 计算 2 的幂次
//         int e2 = countr_zero((unsigned) x);
//         x >>= e2;
//         // 计算 5 的幂次
//         int e5 = 0;
//         while (x % 5 == 0) {
//             e5++;
//             x /= 5;
//         }
//         f[i] = f[i - 1] * x % MOD;
//         p2[i] = p2[i - 1] + e2;
//         p5[i] = p5[i - 1] + e5;
//     }

//     inv_f[MX] = qpow(f[MX], 3); // 欧拉定理求逆元
//     for (int i = MX; i > 0; i--) {
//         int x = i;
//         x >>= countr_zero((unsigned) x);
//         while (x % 5 == 0) {
//             x /= 5;
//         }
//         inv_f[i - 1] = inv_f[i] * x % MOD;
//     }
//     return 0;
// }();

// int comb(int n, int k) {
//     // 由于每项都 < 10，所以无需中途取模
//     return f[n] * inv_f[k] * inv_f[n - k] * qpow(2, p2[n] - p2[k] - p2[n - k]) * qpow(5, p5[n] - p5[k] - p5[n - k]) %
//            MOD;
// }

// class Solution {
// public:
//     bool hasSameDigits(string s) {
//         int x = 0, y = 0;
//         int n = s.size();
//         for (int i = 0; i < s.size() - 1; i++) {
//             x += comb(n - 2, i) * (s[i] - 'a');
//         }
//         for (int i = 1; i < n; i++) {
//             y += comb(n - 2, i - 1) * (s[i] - 'a');
//         }
//         x %= 10;
//         y %= 10;
//         return x == y;
//     }
// };
