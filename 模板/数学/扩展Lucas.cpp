#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
const ll MOD2 = 4611686018427387847;
constexpr int inf = 100'000'005;

// 扩展Lucas定理用于处理模合数,下面是10
// 还用了crt 中国剩余定理

const int MX = 5;
int c[MX][MX];

// 预处理组合数
auto init = []() {
    for (int i = 0; i < MX; i++) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; j++) {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    return 0;
}();

// 计算 C(n, k) % p，要求 p 是质数
int lucas(int n, int k, int p) {
    if (k == 0) {
        return 1;
    }
    return c[n % p][k % p] * lucas(n / p, k / p, p) % p;
};

int comb(int n, int k) {
    // 结果至多为 5 + 4 * 6 = 29，无需中途取模
    return lucas(n, k, 2) * 5 + lucas(n, k, 5) * 6;
}
