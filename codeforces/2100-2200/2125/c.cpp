#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

using ll = long long;

long long countGoodNumbers(long long x) {
    // 我们关心的四个质数
    int primes[] = {2, 3, 5, 7};
    long long result = 0;

    // 遍历这4个质数的所有子集（共 2^4 = 16 个）
    // 使用一个从 0 到 15 的整数 `mask` 作为位掩码
    // mask 的二进制表示中，第 i 位为 1 代表选中第 i 个质数
    for (int mask = 0; mask < 16; ++mask) {
        long long denominator = 1; // 当前子集中质数的乘积（即容斥原理中的分母）
        int sign = 1; // 容斥原理中的符号 (+1 或 -1)

        // 检查 mask 的每一位，以确定当前子集包含哪些质数
        for (int i = 0; i < 4; ++i) {
            // `(mask >> i) & 1` 检查 mask 的第 i 位是否为 1
            if ((mask >> i) & 1) {
                denominator *= primes[i];
                sign *= -1; // 每包含一个质数，符号就反转一次
            }
        }

        // C++ 中的整数除法 `x / denominator` 等同于 Python 的 `x // denominator`
        // 将当前项根据符号加到总结果中
        result += sign * (x / denominator);
    }
    return result;
}

signed main() {
    // 加速 C++ 的输入输出
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // 读取测试用例的数量
    while (t--) {
        long long l, r;
        std::cin >> l >> r; // 读取区间 [l, r]

        // 计算 [l, r] 区间内好数的数量
        // 方法是：计算 [1, r] 的数量，再减去 [1, l-1] 的数量
        long long ans = countGoodNumbers(r) - countGoodNumbers(l - 1);

        std::cout << ans << "\n";
    }

    return 0;
}

// /**
//  * @brief 使用容斥原理计算从 1 到 N 中“好数”的数量.
//  * “好数”定义为不能被 2, 3, 5, 7 中任何一个整除的数.
//  * @param N 上界 (包含)
//  * @return ll [1, N] 区间内好数的数量
//  */
// ll countGoodNumbers(ll N) {
//     if (N == 0) {
//         return 0; // 处理 l-1=0 的边界情况
//     }

//     // N 减去 (能被至少一个单数位质数整除的数的数量)
//     // 根据容斥原理: Total = N - Σ|Aᵢ| + Σ|Aᵢ∩Aⱼ| - ...

//     // Σ|Aᵢ|: 单个质数倍数的和
//     ll sum_singles = N / 2 + N / 3 + N / 5 + N / 7;

//     // Σ|Aᵢ∩Aⱼ|: 两两组合的质数倍数的和
//     ll sum_pairs = N / 6 /*2*3*/ + N / 10 /*2*5*/ + N / 14 /*2*7*/ + N / 15 /*3*5*/ + N / 21 /*3*7*/ + N / 35
//     /*5*7*/;

//     // Σ|Aᵢ∩Aⱼ∩Aₖ|: 三三组合的质数倍数的和
//     ll sum_triples = N / 30 /*2*3*5*/ + N / 42 /*2*3*7*/ + N / 70 /*2*5*7*/ + N / 105 /*3*5*7*/;

//     // 四个组合的质数倍数
//     ll sum_quadruples = N / 210 /*2*3*5*7*/;

//     // 应用容斥原理公式
//     return N - sum_singles + sum_pairs - sum_triples + sum_quadruples;
// }

// void solve() {
//     ll l, r;
//     std::cin >> l >> r;

//     // 区间 [l, r] 的答案 = count(r) - count(l-1)
//     ll result = countGoodNumbers(r) - countGoodNumbers(l - 1);

//     std::cout << result << "\n";
// }

// signed main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     init();
//     int T = 1;
//     cin >> T;
//     while (T--)
//         solve();
//     return 0;
// }
