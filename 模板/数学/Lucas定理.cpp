#include <iostream>

// 为了方便，使用 long long 类型，避免中间计算溢出
using ll = long long;

/**
 * @brief 快速幂函数，计算 (base^exp) % mod
 * * @param base 底数
 * @param exp 指数
 * @param mod 模数
 * @return ll 结果
 */
ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

/**
 * @brief 计算n在模mod下的乘法逆元
 * 要求mod为质数（根据费马小定理）
 * * @param n 要求逆元的数
 * @param mod 模数
 * @return ll n的逆元
 */
ll modInverse(ll n, ll mod) { return power(n, mod - 2, mod); }

/**
 * @brief 计算组合数 C(n, k) % p，其中 n < p
 * 使用公式 C(n, k) = n! / (k! * (n-k)!) % p
 * * @param n 上标
 * @param k 下标
 * @param p 模数 (质数)
 * @return ll 结果
 */
ll combinations(ll n, ll k, ll p) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    // C(n, k) = C(n, n-k)，计算较小的一边
    if (k > n / 2) {
        k = n - k;
    }

    // 计算分子 n * (n-1) * ... * (n-k+1)
    ll numerator = 1;
    for (int i = 0; i < k; ++i) {
        numerator = (numerator * (n - i)) % p;
    }

    // 计算分母 k!
    ll denominator = 1;
    for (int i = 1; i <= k; ++i) {
        denominator = (denominator * i) % p;
    }

    // 返回 分子 * (分母的逆元)
    return (numerator * modInverse(denominator, p)) % p;
}

/**
 * @brief 卢卡斯定理，计算 C(n, k) % p
 * * @param n 上标
 * @param k 下标
 * @param p 模数 (质数)
 * @return ll 结果
 */
ll lucas(ll n, ll k, ll p) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0) {
        return 1;
    }
    return (lucas(n / p, k / p, p) * combinations(n % p, k % p, p)) % p;
}

void solve() {
    ll n, m, p;
    std::cin >> n >> m >> p;

    std::cout << lucas(n + m, n, p) << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
