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

/**
 * @brief 使用容斥原理计算从 1 到 N 中“好数”的数量.
 * “好数”定义为不能被 2, 3, 5, 7 中任何一个整除的数.
 * @param N 上界 (包含)
 * @return ll [1, N] 区间内好数的数量
 */
ll countGoodNumbers(ll N) {
    if (N == 0) {
        return 0; // 处理 l-1=0 的边界情况
    }

    // N 减去 (能被至少一个单数位质数整除的数的数量)
    // 根据容斥原理: Total = N - Σ|Aᵢ| + Σ|Aᵢ∩Aⱼ| - ...

    // Σ|Aᵢ|: 单个质数倍数的和
    ll sum_singles = N / 2 + N / 3 + N / 5 + N / 7;

    // Σ|Aᵢ∩Aⱼ|: 两两组合的质数倍数的和
    ll sum_pairs = N / 6 /*2*3*/ + N / 10 /*2*5*/ + N / 14 /*2*7*/ + N / 15 /*3*5*/ + N / 21 /*3*7*/ + N / 35 /*5*7*/;

    // Σ|Aᵢ∩Aⱼ∩Aₖ|: 三三组合的质数倍数的和
    ll sum_triples = N / 30 /*2*3*5*/ + N / 42 /*2*3*7*/ + N / 70 /*2*5*7*/ + N / 105 /*3*5*7*/;

    // 四个组合的质数倍数
    ll sum_quadruples = N / 210 /*2*3*5*7*/;

    // 应用容斥原理公式
    return N - sum_singles + sum_pairs - sum_triples + sum_quadruples;
}

void solve() {
    ll l, r;
    std::cin >> l >> r;

    // 区间 [l, r] 的答案 = count(r) - count(l-1)
    ll result = countGoodNumbers(r) - countGoodNumbers(l - 1);

    std::cout << result << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
