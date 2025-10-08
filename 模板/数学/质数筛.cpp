//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 埃拉托色尼筛法（Sieve of Eratosthenes）
const int N = 1e6 + 10;
vector<bool> is_prime(N, true); // is_prime[i] 表示 i 是否是质数
vector<int> primes; // 存质数列表

void eratosthenes(int n) {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}

// 线性筛（欧拉筛法）：更快，O(n)
void linear_sieve(int n) {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i])
            primes.push_back(i);
        for (int p: primes) {
            if (p * i > n)
                break;
            is_prime[p * i] = false;
            // 还可以加一个prime_factor[p * i] = p,最小质因数
            if (i % p == 0)
                break; // 保证每个数只被最小质因子筛掉
        }
    }
}

// 最小质因数

vector<int> minp(N + 1), primes;
for (int i = 2; i <= N; i++) {
    if (!minp[i]) {
        minp[i] = i;
        primes.push_back(i);
    }
    for (auto p: primes) {
        if (i * p > m)
            break;
        minp[i * p] = p;
        if (p == minp[i])
            break;
    }
}

// --- 线性筛模板开始 ---
// 筛质因子数量和不同的质因子数量

constexpr int N = 1e7 + 5;

struct Sieve {
    bool is_not_prime[N + 1]{};
    std::vector<int> primes;
    int min_prime_factor[N + 1]{};
    int distinct_factors_count[N + 1]{};

    Sieve() { init(N); }

    void init(int n) {
        is_not_prime[0] = is_not_prime[1] = true;
        min_prime_factor[0] = min_prime_factor[1] = 0;
        distinct_factors_count[1] = 0;

        for (int i = 2; i <= n; ++i) {
            if (!is_not_prime[i]) {
                primes.push_back(i);
                min_prime_factor[i] = i;
                distinct_factors_count[i] = 1;
            }

            for (int p: primes) {
                if ((long long) i * p > n)
                    break;
                is_not_prime[i * p] = true;
                min_prime_factor[i * p] = p;

                if (i % p == 0) {
                    distinct_factors_count[i * p] = distinct_factors_count[i];
                    break;
                } else {
                    distinct_factors_count[i * p] = distinct_factors_count[i] + 1;
                }
            }
        }
    }

    [[nodiscard]] bool is_prime(int x) const {
        if (x <= 1 || x > N)
            return false;
        return !is_not_prime[x];
    }
} sieve;


// --- 线性筛模板结束 ---
